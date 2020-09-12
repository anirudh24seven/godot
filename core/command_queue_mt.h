
/*  command_queue_mt.h                                                   */

#ifndef COMMAND_QUEUE_MT_H
#define COMMAND_QUEUE_MT_H

#include "core/os/memory.h"
#include "core/os/mutex.h"
#include "core/os/semaphore.h"
#include "core/simple_type.h"
#include "core/typedefs.h"

#define COMMA(N) _COMMA_##N
#define _COMMA_0
#define _COMMA_1 ,
#define _COMMA_2 ,
#define _COMMA_3 ,
#define _COMMA_4 ,
#define _COMMA_5 ,
#define _COMMA_6 ,
#define _COMMA_7 ,
#define _COMMA_8 ,
#define _COMMA_9 ,
#define _COMMA_10 ,
#define _COMMA_11 ,
#define _COMMA_12 ,
#define _COMMA_13 ,
#define _COMMA_14 ,
#define _COMMA_15 ,

// 1-based comma separated list of ITEMs
#define COMMA_SEP_LIST(ITEM, LENGTH) _COMMA_SEP_LIST_##LENGTH(ITEM)
#define _COMMA_SEP_LIST_15(ITEM) \
	_COMMA_SEP_LIST_14(ITEM)     \
	, ITEM(15)
#define _COMMA_SEP_LIST_14(ITEM) \
	_COMMA_SEP_LIST_13(ITEM)     \
	, ITEM(14)
#define _COMMA_SEP_LIST_13(ITEM) \
	_COMMA_SEP_LIST_12(ITEM)     \
	, ITEM(13)
#define _COMMA_SEP_LIST_12(ITEM) \
	_COMMA_SEP_LIST_11(ITEM)     \
	, ITEM(12)
#define _COMMA_SEP_LIST_11(ITEM) \
	_COMMA_SEP_LIST_10(ITEM)     \
	, ITEM(11)
#define _COMMA_SEP_LIST_10(ITEM) \
	_COMMA_SEP_LIST_9(ITEM)      \
	, ITEM(10)
#define _COMMA_SEP_LIST_9(ITEM) \
	_COMMA_SEP_LIST_8(ITEM)     \
	, ITEM(9)
#define _COMMA_SEP_LIST_8(ITEM) \
	_COMMA_SEP_LIST_7(ITEM)     \
	, ITEM(8)
#define _COMMA_SEP_LIST_7(ITEM) \
	_COMMA_SEP_LIST_6(ITEM)     \
	, ITEM(7)
#define _COMMA_SEP_LIST_6(ITEM) \
	_COMMA_SEP_LIST_5(ITEM)     \
	, ITEM(6)
#define _COMMA_SEP_LIST_5(ITEM) \
	_COMMA_SEP_LIST_4(ITEM)     \
	, ITEM(5)
#define _COMMA_SEP_LIST_4(ITEM) \
	_COMMA_SEP_LIST_3(ITEM)     \
	, ITEM(4)
#define _COMMA_SEP_LIST_3(ITEM) \
	_COMMA_SEP_LIST_2(ITEM)     \
	, ITEM(3)
#define _COMMA_SEP_LIST_2(ITEM) \
	_COMMA_SEP_LIST_1(ITEM)     \
	, ITEM(2)
#define _COMMA_SEP_LIST_1(ITEM) \
	_COMMA_SEP_LIST_0(ITEM)     \
	ITEM(1)
#define _COMMA_SEP_LIST_0(ITEM)

// 1-based semicolon separated list of ITEMs
#define SEMIC_SEP_LIST(ITEM, LENGTH) _SEMIC_SEP_LIST_##LENGTH(ITEM)
#define _SEMIC_SEP_LIST_15(ITEM) \
	_SEMIC_SEP_LIST_14(ITEM);    \
	ITEM(15)
#define _SEMIC_SEP_LIST_14(ITEM) \
	_SEMIC_SEP_LIST_13(ITEM);    \
	ITEM(14)
#define _SEMIC_SEP_LIST_13(ITEM) \
	_SEMIC_SEP_LIST_12(ITEM);    \
	ITEM(13)
#define _SEMIC_SEP_LIST_12(ITEM) \
	_SEMIC_SEP_LIST_11(ITEM);    \
	ITEM(12)
#define _SEMIC_SEP_LIST_11(ITEM) \
	_SEMIC_SEP_LIST_10(ITEM);    \
	ITEM(11)
#define _SEMIC_SEP_LIST_10(ITEM) \
	_SEMIC_SEP_LIST_9(ITEM);     \
	ITEM(10)
#define _SEMIC_SEP_LIST_9(ITEM) \
	_SEMIC_SEP_LIST_8(ITEM);    \
	ITEM(9)
#define _SEMIC_SEP_LIST_8(ITEM) \
	_SEMIC_SEP_LIST_7(ITEM);    \
	ITEM(8)
#define _SEMIC_SEP_LIST_7(ITEM) \
	_SEMIC_SEP_LIST_6(ITEM);    \
	ITEM(7)
#define _SEMIC_SEP_LIST_6(ITEM) \
	_SEMIC_SEP_LIST_5(ITEM);    \
	ITEM(6)
#define _SEMIC_SEP_LIST_5(ITEM) \
	_SEMIC_SEP_LIST_4(ITEM);    \
	ITEM(5)
#define _SEMIC_SEP_LIST_4(ITEM) \
	_SEMIC_SEP_LIST_3(ITEM);    \
	ITEM(4)
#define _SEMIC_SEP_LIST_3(ITEM) \
	_SEMIC_SEP_LIST_2(ITEM);    \
	ITEM(3)
#define _SEMIC_SEP_LIST_2(ITEM) \
	_SEMIC_SEP_LIST_1(ITEM);    \
	ITEM(2)
#define _SEMIC_SEP_LIST_1(ITEM) \
	_SEMIC_SEP_LIST_0(ITEM)     \
	ITEM(1)
#define _SEMIC_SEP_LIST_0(ITEM)

// 1-based space separated list of ITEMs
#define SPACE_SEP_LIST(ITEM, LENGTH) _SPACE_SEP_LIST_##LENGTH(ITEM)
#define _SPACE_SEP_LIST_15(ITEM) \
	_SPACE_SEP_LIST_14(ITEM)     \
	ITEM(15)
#define _SPACE_SEP_LIST_14(ITEM) \
	_SPACE_SEP_LIST_13(ITEM)     \
	ITEM(14)
#define _SPACE_SEP_LIST_13(ITEM) \
	_SPACE_SEP_LIST_12(ITEM)     \
	ITEM(13)
#define _SPACE_SEP_LIST_12(ITEM) \
	_SPACE_SEP_LIST_11(ITEM)     \
	ITEM(12)
#define _SPACE_SEP_LIST_11(ITEM) \
	_SPACE_SEP_LIST_10(ITEM)     \
	ITEM(11)
#define _SPACE_SEP_LIST_10(ITEM) \
	_SPACE_SEP_LIST_9(ITEM)      \
	ITEM(10)
#define _SPACE_SEP_LIST_9(ITEM) \
	_SPACE_SEP_LIST_8(ITEM)     \
	ITEM(9)
#define _SPACE_SEP_LIST_8(ITEM) \
	_SPACE_SEP_LIST_7(ITEM)     \
	ITEM(8)
#define _SPACE_SEP_LIST_7(ITEM) \
	_SPACE_SEP_LIST_6(ITEM)     \
	ITEM(7)
#define _SPACE_SEP_LIST_6(ITEM) \
	_SPACE_SEP_LIST_5(ITEM)     \
	ITEM(6)
#define _SPACE_SEP_LIST_5(ITEM) \
	_SPACE_SEP_LIST_4(ITEM)     \
	ITEM(5)
#define _SPACE_SEP_LIST_4(ITEM) \
	_SPACE_SEP_LIST_3(ITEM)     \
	ITEM(4)
#define _SPACE_SEP_LIST_3(ITEM) \
	_SPACE_SEP_LIST_2(ITEM)     \
	ITEM(3)
#define _SPACE_SEP_LIST_2(ITEM) \
	_SPACE_SEP_LIST_1(ITEM)     \
	ITEM(2)
#define _SPACE_SEP_LIST_1(ITEM) \
	_SPACE_SEP_LIST_0(ITEM)     \
	ITEM(1)
#define _SPACE_SEP_LIST_0(ITEM)

#define ARG(N) p##N
#define PARAM(N) P##N p##N
#define TYPE_PARAM(N) class P##N
#define PARAM_DECL(N) typename GetSimpleTypeT<P##N>::type_t p##N

#define DECL_CMD(N)                                                    \
	template <class T, class M COMMA(N) COMMA_SEP_LIST(TYPE_PARAM, N)> \
	struct Command##N : public CommandBase {                           \
		T *instance;                                                   \
		M method;                                                      \
		SEMIC_SEP_LIST(PARAM_DECL, N);                                 \
		virtual void call() {                                          \
			(instance->*method)(COMMA_SEP_LIST(ARG, N));               \
		}                                                              \
	};

#define DECL_CMD_RET(N)                                                         \
	template <class T, class M, COMMA_SEP_LIST(TYPE_PARAM, N) COMMA(N) class R> \
	struct CommandRet##N : public SyncCommand {                                 \
		R *ret;                                                                 \
		T *instance;                                                            \
		M method;                                                               \
		SEMIC_SEP_LIST(PARAM_DECL, N);                                          \
		virtual void call() {                                                   \
			*ret = (instance->*method)(COMMA_SEP_LIST(ARG, N));                 \
		}                                                                       \
	};

#define DECL_CMD_SYNC(N)                                               \
	template <class T, class M COMMA(N) COMMA_SEP_LIST(TYPE_PARAM, N)> \
	struct CommandSync##N : public SyncCommand {                       \
		T *instance;                                                   \
		M method;                                                      \
		SEMIC_SEP_LIST(PARAM_DECL, N);                                 \
		virtual void call() {                                          \
			(instance->*method)(COMMA_SEP_LIST(ARG, N));               \
		}                                                              \
	};

#define TYPE_ARG(N) P##N
#define CMD_TYPE(N) Command##N<T, M COMMA(N) COMMA_SEP_LIST(TYPE_ARG, N)>
#define CMD_ASSIGN_PARAM(N) cmd->p##N = p##N

#define DECL_PUSH(N)                                                         \
	template <class T, class M COMMA(N) COMMA_SEP_LIST(TYPE_PARAM, N)>       \
	void push(T *p_instance, M p_method COMMA(N) COMMA_SEP_LIST(PARAM, N)) { \
		CMD_TYPE(N) *cmd = allocate_and_lock<CMD_TYPE(N)>();                 \
		cmd->instance = p_instance;                                          \
		cmd->method = p_method;                                              \
		SEMIC_SEP_LIST(CMD_ASSIGN_PARAM, N);                                 \
		unlock();                                                            \
		if (sync)                                                            \
			sync->post();                                                    \
	}

#define CMD_RET_TYPE(N) CommandRet##N<T, M, COMMA_SEP_LIST(TYPE_ARG, N) COMMA(N) R>

#define DECL_PUSH_AND_RET(N)                                                                   \
	template <class T, class M, COMMA_SEP_LIST(TYPE_PARAM, N) COMMA(N) class R>                \
	void push_and_ret(T *p_instance, M p_method, COMMA_SEP_LIST(PARAM, N) COMMA(N) R *r_ret) { \
		SyncSemaphore *ss = _alloc_sync_sem();                                                 \
		CMD_RET_TYPE(N) *cmd = allocate_and_lock<CMD_RET_TYPE(N)>();                           \
		cmd->instance = p_instance;                                                            \
		cmd->method = p_method;                                                                \
		SEMIC_SEP_LIST(CMD_ASSIGN_PARAM, N);                                                   \
		cmd->ret = r_ret;                                                                      \
		cmd->sync_sem = ss;                                                                    \
		unlock();                                                                              \
		if (sync)                                                                              \
			sync->post();                                                                      \
		ss->sem.wait();                                                                        \
		ss->in_use = false;                                                                    \
	}

#define CMD_SYNC_TYPE(N) CommandSync##N<T, M COMMA(N) COMMA_SEP_LIST(TYPE_ARG, N)>

#define DECL_PUSH_AND_SYNC(N)                                                         \
	template <class T, class M COMMA(N) COMMA_SEP_LIST(TYPE_PARAM, N)>                \
	void push_and_sync(T *p_instance, M p_method COMMA(N) COMMA_SEP_LIST(PARAM, N)) { \
		SyncSemaphore *ss = _alloc_sync_sem();                                        \
		CMD_SYNC_TYPE(N) *cmd = allocate_and_lock<CMD_SYNC_TYPE(N)>();                \
		cmd->instance = p_instance;                                                   \
		cmd->method = p_method;                                                       \
		SEMIC_SEP_LIST(CMD_ASSIGN_PARAM, N);                                          \
		cmd->sync_sem = ss;                                                           \
		unlock();                                                                     \
		if (sync)                                                                     \
			sync->post();                                                             \
		ss->sem.wait();                                                               \
		ss->in_use = false;                                                           \
	}

#define MAX_CMD_PARAMS 15

class CommandQueueMT {
	struct SyncSemaphore {
		Semaphore sem;
		bool in_use = false;
	};

	struct CommandBase {
		virtual void call() = 0;
		virtual void post() {}
		virtual ~CommandBase() {}
	};

	struct SyncCommand : public CommandBase {
		SyncSemaphore *sync_sem;

		virtual void post() {
			sync_sem->sem.post();
		}
	};

	DECL_CMD(0)
	SPACE_SEP_LIST(DECL_CMD, 15)

	/* comands that return */
	DECL_CMD_RET(0)
	SPACE_SEP_LIST(DECL_CMD_RET, 15)

	/* commands that don't return but sync */
	DECL_CMD_SYNC(0)
	SPACE_SEP_LIST(DECL_CMD_SYNC, 15)

	/***** BASE *******/

	enum {
		COMMAND_MEM_SIZE_KB = 256,
		COMMAND_MEM_SIZE = COMMAND_MEM_SIZE_KB * 1024,
		SYNC_SEMAPHORES = 8
	};

	uint8_t *command_mem = (uint8_t *)memalloc(COMMAND_MEM_SIZE);
	uint32_t read_ptr = 0;
	uint32_t write_ptr = 0;
	uint32_t dealloc_ptr = 0;
	SyncSemaphore sync_sems[SYNC_SEMAPHORES];
	Mutex mutex;
	Semaphore *sync = nullptr;

	template <class T>
	T *allocate() {
		// alloc size is size+T+safeguard
		uint32_t alloc_size = ((sizeof(T) + 8 - 1) & ~(8 - 1)) + 8;

	tryagain:

		if (write_ptr < dealloc_ptr) {
			// behind dealloc_ptr, check that there is room
			if ((dealloc_ptr - write_ptr) <= alloc_size) {
				// There is no more room, try to deallocate something
				if (dealloc_one()) {
					goto tryagain;
				}
				return nullptr;
			}
		} else {
			// ahead of dealloc_ptr, check that there is room

			if ((COMMAND_MEM_SIZE - write_ptr) < alloc_size + sizeof(uint32_t)) {
				// no room at the end, wrap down;

				if (dealloc_ptr == 0) { // don't want write_ptr to become dealloc_ptr

					// There is no more room, try to deallocate something
					if (dealloc_one()) {
						goto tryagain;
					}
					return nullptr;
				}

				// if this happens, it's a bug
				ERR_FAIL_COND_V((COMMAND_MEM_SIZE - write_ptr) < 8, nullptr);
				// zero means, wrap to beginning

				uint32_t *p = (uint32_t *)&command_mem[write_ptr];
				*p = 0;
				write_ptr = 0;
				goto tryagain;
			}
		}
		// Allocate the size and the 'in use' bit.
		// First bit used to mark if command is still in use (1)
		// or if it has been destroyed and can be deallocated (0).
		uint32_t size = (sizeof(T) + 8 - 1) & ~(8 - 1);
		uint32_t *p = (uint32_t *)&command_mem[write_ptr];
		*p = (size << 1) | 1;
		write_ptr += 8;
		// allocate the command
		T *cmd = memnew_placement(&command_mem[write_ptr], T);
		write_ptr += size;
		return cmd;
	}

	template <class T>
	T *allocate_and_lock() {
		lock();
		T *ret;

		while ((ret = allocate<T>()) == nullptr) {
			unlock();
			// sleep a little until fetch happened and some room is made
			wait_for_flush();
			lock();
		}

		return ret;
	}

	bool flush_one(bool p_lock = true) {
		if (p_lock) {
			lock();
		}
	tryagain:

		// tried to read an empty queue
		if (read_ptr == write_ptr) {
			if (p_lock) {
				unlock();
			}
			return false;
		}

		uint32_t size_ptr = read_ptr;
		uint32_t size = *(uint32_t *)&command_mem[read_ptr] >> 1;

		if (size == 0) {
			//end of ringbuffer, wrap
			read_ptr = 0;
			goto tryagain;
		}

		read_ptr += 8;

		CommandBase *cmd = reinterpret_cast<CommandBase *>(&command_mem[read_ptr]);

		read_ptr += size;

		if (p_lock) {
			unlock();
		}
		cmd->call();
		if (p_lock) {
			lock();
		}

		cmd->post();
		cmd->~CommandBase();
		*(uint32_t *)&command_mem[size_ptr] &= ~1;

		if (p_lock) {
			unlock();
		}
		return true;
	}

	void lock();
	void unlock();
	void wait_for_flush();
	SyncSemaphore *_alloc_sync_sem();
	bool dealloc_one();

public:
	/* NORMAL PUSH COMMANDS */
	DECL_PUSH(0)
	SPACE_SEP_LIST(DECL_PUSH, 15)

	/* PUSH AND RET COMMANDS */
	DECL_PUSH_AND_RET(0)
	SPACE_SEP_LIST(DECL_PUSH_AND_RET, 15)

	/* PUSH AND RET SYNC COMMANDS*/
	DECL_PUSH_AND_SYNC(0)
	SPACE_SEP_LIST(DECL_PUSH_AND_SYNC, 15)

	void wait_and_flush_one() {
		ERR_FAIL_COND(!sync);
		sync->wait();
		flush_one();
	}

	void flush_all() {
		//ERR_FAIL_COND(sync);
		lock();
		while (flush_one(false)) {
		}
		unlock();
	}

	CommandQueueMT(bool p_sync);
	~CommandQueueMT();
};

#undef ARG
#undef PARAM
#undef TYPE_PARAM
#undef PARAM_DECL
#undef DECL_CMD
#undef DECL_CMD_RET
#undef DECL_CMD_SYNC
#undef TYPE_ARG
#undef CMD_TYPE
#undef CMD_ASSIGN_PARAM
#undef DECL_PUSH
#undef CMD_RET_TYPE
#undef DECL_PUSH_AND_RET
#undef CMD_SYNC_TYPE
#undef DECL_CMD_SYNC

#endif // COMMAND_QUEUE_MT_H
