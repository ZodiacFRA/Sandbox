import json

import bpy


class object(object):
    def __init__(self, name):
        # ALL
        self.name = name
        self.type
        self.pos
        # NOT LIGHTS
        self.mesh_name
        self.tex_name
        self.rot
        self.size
        # LIGHTS
        self.power
        self.color

    def serialize(self):
        if self.type == "LIGHTS"
            return {type: self.type, pos: self.pos, power: self.power, color: self.color}
        return {type: self.type, pos: self.pos, mesh_name: self.mesh_name, tex_name: self.tex_name, rot: self.rot, size: self.size}


EXPORT_PATH = "/home/zodiac/Code/Perso/GamesTests/Sandbox/assets/maps"

if __name__ == '__main__':
    level_name = "test" #input("Enter map name: ")
    objs_export_path = f"{EXPORT_PATH}/{level_name}/OBJS"
    if not os.path.exists(objs_export_path):
        os.mkdir(objs_export_path)

    exported_meshes = {}
    for obj in bpy.data.objects:
        obj.select = True
        print(f"Exporting {obj.name}")
        res.name = object(obj.name)
        res.type = obj.type
        res.pos = JSON

        if obj.type == "MESH" or obj.type == "PLAYER":
            res.mesh_name = obj.data.type
            if res.mesh_name not in exported_meshes:
                bpy.ops.export_scene.obj(filepath=f"{objs_export_path}/{res.mesh_name}.obj",
                check_existing=False, axis_forward='-Z', axis_up='Y',
                filter_glob="*.obj;*.mtl", use_selection=True, use_animation=False,
                use_mesh_modifiers=True, use_edges=True, use_smooth_groups=False,
                use_smooth_groups_bitflags=False, use_normals=True, use_uvs=True,
                use_materials=False, use_triangles=True, use_nurbs=False, use_vertex_groups=False,
                use_blen_objects=True, group_by_object=False, group_by_material=False,
                keep_vertex_order=False, global_scale=1, path_mode='ABSOLUTE'
                )
                exported_meshes.append(res.mesh_name)

            res.tex_name = "test.bmp"
            res.rot = obj.rotation_euler
            res.size = obj.dimensions

        elif obj.type == "LIGHT":
            res.power = 10
            res.color = None
        else:
            print(f"Unknown obj type: {obj.type}")
        exported_meshes[res.name] = res.serialize()

    json = json.dumps(exported_meshes)
