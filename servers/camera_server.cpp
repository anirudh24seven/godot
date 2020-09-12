
/*  camera_server.cpp                                                    */

#include "camera_server.h"
#include "rendering_server.h"
#include "servers/camera/camera_feed.h"

////////////////////////////////////////////////////////
// CameraServer

CameraServer::CreateFunc CameraServer::create_func = nullptr;

void CameraServer::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_feed", "index"), &CameraServer::get_feed);
	ClassDB::bind_method(D_METHOD("get_feed_count"), &CameraServer::get_feed_count);
	ClassDB::bind_method(D_METHOD("feeds"), &CameraServer::get_feeds);

	ClassDB::bind_method(D_METHOD("add_feed", "feed"), &CameraServer::add_feed);
	ClassDB::bind_method(D_METHOD("remove_feed", "feed"), &CameraServer::remove_feed);

	ADD_SIGNAL(MethodInfo("camera_feed_added", PropertyInfo(Variant::INT, "id")));
	ADD_SIGNAL(MethodInfo("camera_feed_removed", PropertyInfo(Variant::INT, "id")));

	BIND_ENUM_CONSTANT(FEED_RGBA_IMAGE);
	BIND_ENUM_CONSTANT(FEED_YCBCR_IMAGE);
	BIND_ENUM_CONSTANT(FEED_Y_IMAGE);
	BIND_ENUM_CONSTANT(FEED_CBCR_IMAGE);
};

CameraServer *CameraServer::singleton = nullptr;

CameraServer *CameraServer::get_singleton() {
	return singleton;
};

int CameraServer::get_free_id() {
	bool id_exists = true;
	int newid = 0;

	// find a free id
	while (id_exists) {
		newid++;
		id_exists = false;
		for (int i = 0; i < feeds.size() && !id_exists; i++) {
			if (feeds[i]->get_id() == newid) {
				id_exists = true;
			};
		};
	};

	return newid;
};

int CameraServer::get_feed_index(int p_id) {
	for (int i = 0; i < feeds.size(); i++) {
		if (feeds[i]->get_id() == p_id) {
			return i;
		};
	};

	return -1;
};

Ref<CameraFeed> CameraServer::get_feed_by_id(int p_id) {
	int index = get_feed_index(p_id);

	if (index == -1) {
		return nullptr;
	} else {
		return feeds[index];
	}
};

void CameraServer::add_feed(const Ref<CameraFeed> &p_feed) {
	// add our feed
	feeds.push_back(p_feed);

// record for debugging
#ifdef DEBUG_ENABLED
	print_line("Registered camera " + p_feed->get_name() + " with id " + itos(p_feed->get_id()) + " position " + itos(p_feed->get_position()) + " at index " + itos(feeds.size() - 1));
#endif

	// let whomever is interested know
	emit_signal("camera_feed_added", p_feed->get_id());
};

void CameraServer::remove_feed(const Ref<CameraFeed> &p_feed) {
	for (int i = 0; i < feeds.size(); i++) {
		if (feeds[i] == p_feed) {
			int feed_id = p_feed->get_id();

// record for debugging
#ifdef DEBUG_ENABLED
			print_line("Removed camera " + p_feed->get_name() + " with id " + itos(feed_id) + " position " + itos(p_feed->get_position()));
#endif

			// remove it from our array, if this results in our feed being unreferenced it will be destroyed
			feeds.remove(i);

			// let whomever is interested know
			emit_signal("camera_feed_removed", feed_id);
			return;
		};
	};
};

Ref<CameraFeed> CameraServer::get_feed(int p_index) {
	ERR_FAIL_INDEX_V(p_index, feeds.size(), nullptr);

	return feeds[p_index];
};

int CameraServer::get_feed_count() {
	return feeds.size();
};

Array CameraServer::get_feeds() {
	Array return_feeds;
	int cc = get_feed_count();
	return_feeds.resize(cc);

	for (int i = 0; i < feeds.size(); i++) {
		return_feeds[i] = get_feed(i);
	};

	return return_feeds;
};

RID CameraServer::feed_texture(int p_id, CameraServer::FeedImage p_texture) {
	int index = get_feed_index(p_id);
	ERR_FAIL_COND_V(index == -1, RID());

	Ref<CameraFeed> feed = get_feed(index);

	return feed->get_texture(p_texture);
};

CameraServer::CameraServer() {
	singleton = this;
};

CameraServer::~CameraServer() {
	singleton = nullptr;
};
