
/*  material_editor_plugin.h                                             */

#ifndef MATERIAL_EDITOR_PLUGIN_H
#define MATERIAL_EDITOR_PLUGIN_H

#include "editor/property_editor.h"
#include "scene/resources/primitive_meshes.h"

#include "editor/editor_node.h"
#include "editor/editor_plugin.h"
#include "scene/3d/camera_3d.h"
#include "scene/3d/light_3d.h"
#include "scene/3d/mesh_instance_3d.h"
#include "scene/resources/material.h"

class SubViewportContainer;

class MaterialEditor : public Control {
	GDCLASS(MaterialEditor, Control);

	SubViewportContainer *vc;
	SubViewport *viewport;
	MeshInstance3D *sphere_instance;
	MeshInstance3D *box_instance;
	DirectionalLight3D *light1;
	DirectionalLight3D *light2;
	Camera3D *camera;

	Ref<SphereMesh> sphere_mesh;
	Ref<CubeMesh> box_mesh;

	TextureButton *sphere_switch;
	TextureButton *box_switch;

	TextureButton *light_1_switch;
	TextureButton *light_2_switch;

	Ref<Material> material;

	void _button_pressed(Node *p_button);
	bool first_enter;

protected:
	void _notification(int p_what);

	static void _bind_methods();

public:
	void edit(Ref<Material> p_material, const Ref<Environment> &p_env);
	MaterialEditor();
};

class EditorInspectorPluginMaterial : public EditorInspectorPlugin {
	GDCLASS(EditorInspectorPluginMaterial, EditorInspectorPlugin);
	Ref<Environment> env;

public:
	virtual bool can_handle(Object *p_object) override;
	virtual void parse_begin(Object *p_object) override;

	EditorInspectorPluginMaterial();
};

class MaterialEditorPlugin : public EditorPlugin {
	GDCLASS(MaterialEditorPlugin, EditorPlugin);

public:
	virtual String get_name() const override { return "Material"; }

	MaterialEditorPlugin(EditorNode *p_node);
};

class StandardMaterial3DConversionPlugin : public EditorResourceConversionPlugin {
	GDCLASS(StandardMaterial3DConversionPlugin, EditorResourceConversionPlugin);

public:
	virtual String converts_to() const override;
	virtual bool handles(const Ref<Resource> &p_resource) const override;
	virtual Ref<Resource> convert(const Ref<Resource> &p_resource) const override;
};

class ParticlesMaterialConversionPlugin : public EditorResourceConversionPlugin {
	GDCLASS(ParticlesMaterialConversionPlugin, EditorResourceConversionPlugin);

public:
	virtual String converts_to() const override;
	virtual bool handles(const Ref<Resource> &p_resource) const override;
	virtual Ref<Resource> convert(const Ref<Resource> &p_resource) const override;
};

class CanvasItemMaterialConversionPlugin : public EditorResourceConversionPlugin {
	GDCLASS(CanvasItemMaterialConversionPlugin, EditorResourceConversionPlugin);

public:
	virtual String converts_to() const override;
	virtual bool handles(const Ref<Resource> &p_resource) const override;
	virtual Ref<Resource> convert(const Ref<Resource> &p_resource) const override;
};

class ProceduralSkyMaterialConversionPlugin : public EditorResourceConversionPlugin {
	GDCLASS(ProceduralSkyMaterialConversionPlugin, EditorResourceConversionPlugin);

public:
	virtual String converts_to() const override;
	virtual bool handles(const Ref<Resource> &p_resource) const override;
	virtual Ref<Resource> convert(const Ref<Resource> &p_resource) const override;
};

class PanoramaSkyMaterialConversionPlugin : public EditorResourceConversionPlugin {
	GDCLASS(PanoramaSkyMaterialConversionPlugin, EditorResourceConversionPlugin);

public:
	virtual String converts_to() const override;
	virtual bool handles(const Ref<Resource> &p_resource) const override;
	virtual Ref<Resource> convert(const Ref<Resource> &p_resource) const override;
};

class PhysicalSkyMaterialConversionPlugin : public EditorResourceConversionPlugin {
	GDCLASS(PhysicalSkyMaterialConversionPlugin, EditorResourceConversionPlugin);

public:
	virtual String converts_to() const override;
	virtual bool handles(const Ref<Resource> &p_resource) const override;
	virtual Ref<Resource> convert(const Ref<Resource> &p_resource) const override;
};

#endif // MATERIAL_EDITOR_PLUGIN_H
