
/*  command_queue_mt.cpp                                                 */



#include "command_queue_mt.h"

#include "core/os/os.h"

void CommandQueueMT::lock() {
	mutex.lock();
}

void CommandQueueMT::unlock() {
	mutex.unlock();
}

void CommandQueueMT::wait_for_flush() {
	// wait one millisecond for a flush to happen
	OS::get_singleton()->delay_usec(1000);
}

CommandQueueMT::SyncSemaphore *CommandQueueMT::_alloc_sync_sem() {
	int idx = -1;

	while (true) {
		lock();
		for (int i = 0; i < SYNC_SEMAPHORES; i++) {
			if (!sync_sems[i].in_use) {
				sync_sems[i].in_use = true;
				idx = i;
				break;
			}
		}
		unlock();

		if (idx == -1) {
			wait_for_flush();
		} else {
			break;
		}
	}

	return &sync_sems[idx];
}

bool CommandQueueMT::dealloc_one() {
tryagain:
	if (dealloc_ptr == write_ptr) {
		// The queue is empty
		return false;
	}

	uint32_t size = *(uint32_t *)&command_mem[dealloc_ptr];

	if (size == 0) {
		// End of command buffer wrap down
		dealloc_ptr = 0;
		goto tryagain;
	}

	if (size & 1) {
		// Still used, nothing can be deallocated
		return false;
	}

	dealloc_ptr += (size >> 1) + 8;
	return true;
}

CommandQueueMT::CommandQueueMT(bool p_sync) {
	if (p_sync) {
		sync = memnew(Semaphore);
	}
}

CommandQueueMT::~CommandQueueMT() {
	if (sync) {
		memdelete(sync);
	}
	memfree(command_mem);
}
