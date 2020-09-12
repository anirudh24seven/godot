
/*  bone_attachment_3d.h                                                 */

#ifndef BONE_ATTACHMENT_H
#define BONE_ATTACHMENT_H

#include "scene/3d/skeleton_3d.h"

class BoneAttachment3D : public Node3D {
	GDCLASS(BoneAttachment3D, Node3D);

	bool bound;
	String bone_name;

	void _check_bind();
	void _check_unbind();

protected:
	virtual void _validate_property(PropertyInfo &property) const override;
	void _notification(int p_what);

	static void _bind_methods();

public:
	void set_bone_name(const String &p_name);
	String get_bone_name() const;

	BoneAttachment3D();
};

#endif // BONE_ATTACHMENT_H
