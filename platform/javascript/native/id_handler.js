
/*  id_handler.js                                                        */

var IDHandler = /** @constructor */ function() {

	var ids = {};
	var size = 0;

	this.has = function(id) {
		return ids.hasOwnProperty(id);
	}

	this.add = function(obj) {
		size += 1;
		var id = crypto.getRandomValues(new Int32Array(32))[0];
		ids[id] = obj;
		return id;
	}

	this.get = function(id) {
		return ids[id];
	}

	this.remove = function(id) {
		size -= 1;
		delete ids[id];
	}

	this.size = function() {
		return size;
	}

	this.ids = ids;
};

Module.IDHandler = new IDHandler;
