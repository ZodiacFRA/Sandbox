import json
import os
import shutil

import bpy


class obj_struct(object):
    def __init__(self, name):
        # ALL
        self.name = name
        self.type = None
        self.pos = None
        # NOT LIGHTS
        self.mesh_name = None
        self.tex_name = None
        self.rot = None
        self.size = None
        # LIGHTS
        self.power = None
        self.color = None

    def serialize(self):
        if self.type == "LIGHT":
            return {"type": self.type, "pos": self.pos, "power": self.power, "color": self.color}
        return {"type": self.type, "pos": self.pos, "mesh_name": self.mesh_name, "tex_name": self.tex_name, "rot": self.rot, "size": self.size}


EXPORT_PATH = "/home/zodiac/Code/Perso/GamesTests/Sandbox/assets/maps"

if __name__ == '__main__':
    print('-'*50)
    level_name = input("Enter map name: ")
    objs_export_path = f"{EXPORT_PATH}/{level_name}/OBJS"
    if os.path.exists(objs_export_path):
        shutil.rmtree(objs_export_path)
    os.makedirs(objs_export_path)
    # Deselect all objects in the scene
    for obj in bpy.data.objects:
        obj.select_set(state=False)

    final_dict = {}
    exported_meshes = []
    for obj in bpy.data.objects:
        print(f"Exporting {obj.name}")
        res = obj_struct(obj.name)
        print(obj.name[:6])
        if obj.name[:6] == "Player":
            res.type = "PLAYER"
        else:
            res.type = obj.type
        res.pos = [obj.location[0], obj.location[1], obj.location[2]]


        if obj.type == "MESH":
            res.mesh_name = obj.data.name
            if res.mesh_name not in exported_meshes:
                # If we don't do that, the location will be stored in the .obj as well
                obj.location = (0, 0, 0)
                obj.select_set(state=True)
                bpy.ops.export_scene.obj(filepath=f"{objs_export_path}/{res.mesh_name}.obj",
                                    check_existing=False, axis_forward='-Z', axis_up='Y',
                                    filter_glob="*.obj;*.mtl", use_selection=True, use_animation=False,
                                    use_mesh_modifiers=True, use_edges=True, use_smooth_groups=False,
                                    use_smooth_groups_bitflags=False, use_normals=True, use_uvs=True,
                                    use_materials=False, use_triangles=True, use_nurbs=False, use_vertex_groups=False,
                                    use_blen_objects=True, group_by_object=False, group_by_material=False,
                                    keep_vertex_order=False, global_scale=1, path_mode='ABSOLUTE'
                )
                obj.location = res.pos
                obj.select_set(state=False)
                exported_meshes.append(res.mesh_name)

            res.tex_name = "test.bmp"
            res.rot = [obj.rotation_euler[0], obj.rotation_euler[1], obj.rotation_euler[2]]
            res.size = [obj.dimensions[0], obj.dimensions[1], obj.dimensions[2]]

        elif obj.type == "LIGHT":
            res.power = 10
            res.color = None
        else:
            print(f"Unknown obj type: {obj.type}")

        final_dict[res.name] = res.serialize()

    with open(f"{EXPORT_PATH}/{level_name}/{level_name}.json", 'w', encoding="utf-8") as f:
        f.write(json.dumps(final_dict))
