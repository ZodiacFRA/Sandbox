import json
import os
import shutil

import bpy

EXPORT_PATH = "/home/zodiac/Code/Perso/GamesTests/Sandbox/assets/maps"


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
        # PLAYER ONLY
        self.player_idx = 0

    def serialize(self):
        if self.type == "LIGHT":
            return {"type": self.type, "pos": self.pos, "power": self.power, "color": self.color}
        res = {
            "type": self.type, "pos": self.pos, "mesh_name": self.mesh_name, "tex_name": self.tex_name,
            "rot": self.rot, "size": self.size
        }
        if self.type == "PLAYER":
            res["player_idx"] = self.player_idx
        return res


class SceneParser(object):
    def __init__(self, level_name):
        self.level_name = level_name
        self.obj_export_path = f"{EXPORT_PATH}/{level_name}/Objs"
        self.tex_export_path = f"{EXPORT_PATH}/{level_name}/Textures"
        self.final_dict = {}
        self.exported_meshes = []

    def init(self):
        if os.path.exists(f"{EXPORT_PATH}/{self.level_name}"):
            shutil.rmtree(f"{EXPORT_PATH}/{self.level_name}")
        os.makedirs(self.obj_export_path)
        os.makedirs(self.tex_export_path)
        # Deselect all objects in the scene
        for obj in bpy.data.objects:
            obj.select_set(state=False)

    def handle_texture(self, obj):
        return "test.bmp"

    def handle_mesh(self, obj, tmp_obj_struct):
        tmp_obj_struct.mesh_name = obj.data.name
        if tmp_obj_struct.mesh_name not in self.exported_meshes:
            # If we don't do that, the location will be stored in the .obj as well
            obj.location = (0, 0, 0)
            obj.select_set(state=True)
            bpy.ops.export_scene.obj(filepath=f"{self.obj_export_path}/{tmp_obj_struct.mesh_name}.obj",
                                check_existing=False, axis_forward='-Z', axis_up='Y',
                                filter_glob="*.obj;*.mtl", use_selection=True, use_animation=False,
                                use_mesh_modifiers=True, use_edges=True, use_smooth_groups=False,
                                use_smooth_groups_bitflags=False, use_normals=True, use_uvs=True,
                                use_materials=False, use_triangles=True, use_nurbs=False,
                                use_vertex_groups=False, use_blen_objects=True, group_by_object=False,
                                group_by_material=False, keep_vertex_order=False, global_scale=1,
                                path_mode='ABSOLUTE'
            )
            obj.location = tmp_obj_struct.pos
            obj.select_set(state=False)
            self.exported_meshes.append(tmp_obj_struct.mesh_name)

        tmp_obj_struct.tex_name = self.handle_texture(obj)
        tmp_obj_struct.rot = [obj.rotation_euler[0], obj.rotation_euler[1], obj.rotation_euler[2]]
        tmp_obj_struct.size = [obj.dimensions[0], obj.dimensions[1], obj.dimensions[2]]

    def get_parsed_scene(self):
        for obj in bpy.data.objects:
            print(f"Exporting {obj.name}")
            tmp_obj_struct = obj_struct(obj.name)

            if obj.name[:6] == "Player":
                tmp_obj_struct.type = "PLAYER"
                tmp_obj_struct.player_idx = obj.name[6]
            else:
                tmp_obj_struct.type = obj.type
            tmp_obj_struct.pos = [obj.location[0], obj.location[1], obj.location[2]]

            if obj.type == "MESH":
                self.handle_mesh(obj, tmp_obj_struct)
            elif obj.type == "LIGHT":
                tmp_obj_struct.power = 10
                tmp_obj_struct.color = None
            else:
                print(f"Unknown obj type: {obj.type}")

            self.final_dict[tmp_obj_struct.name] = tmp_obj_struct.serialize()

        return self.final_dict


if __name__ == '__main__':
    print('-'*50)
    level_name = input("Enter map name: ")

    scene_parser = SceneParser(level_name)
    scene_parser.init()
    scene = scene_parser.get_parsed_scene()

    with open(f"{EXPORT_PATH}/{level_name}/{level_name}.json", 'w', encoding="utf-8") as f:
        f.write(json.dumps(scene))
