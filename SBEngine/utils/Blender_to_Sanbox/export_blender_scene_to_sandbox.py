import json
import os
import shutil
from struct import pack

import bpy


C_RED = "\x1b[31m"
C_YELLOW = "\x1b[33m"
C_GREEN = "\x1b[32m"
C_BLUE = "\x1b[36m"
C_RESET = "\x1b[0m"
EXPORT_PATH = "/home/zodiac/Code/Perso/GamesTests/Sandbox/assets/maps"


class SceneParser(object):
    def __init__(self, level_name):
        self.level_name = level_name
        self.obj_export_path = f"{EXPORT_PATH}/{level_name}/Objs/"
        self.tex_export_path = f"{EXPORT_PATH}/{level_name}/Textures/"
        self.final_dict = {}
        self.exported_meshes = []
        self.exported_colors = []

    def init(self):
        if os.path.exists(f"{EXPORT_PATH}/{self.level_name}"):
            shutil.rmtree(f"{EXPORT_PATH}/{self.level_name}")
        os.makedirs(self.obj_export_path)
        os.makedirs(self.tex_export_path)
        # Deselect all objects in the scene
        for obj in bpy.data.objects:
            obj.select_set(state=False)

    def handle_texture(self, obj):
        """Only handle color for now, no textures"""
        if not obj.active_material:
            print(f"{C_YELLOW}No active material{C_RESET}")
        else:
            print(f"{C_BLUE}Material: {obj.active_material.name}{C_RESET}")
            for n in obj.active_material.node_tree.nodes:
                if n.type=='BSDF_PRINCIPLED':
                    mat_color = [int(a*255) for a in n.inputs[0].default_value[:3]]
                    if mat_color not in self.exported_colors:
                        print(f"{C_BLUE}Creating bmp texture for color {mat_color}{C_RESET}")
                        self.exported_colors.append(mat_color)
                        return self.create_tex_from_color(mat_color)
        return "fallback.bmp"

    def handle_mesh(self, obj, tmp_obj_struct):
        tmp_obj_struct.mesh_name = obj.data.name
        if tmp_obj_struct.mesh_name not in self.exported_meshes:
            # If we don't do that, the location will be stored in the .obj as well
            obj.location = (0, 0, 0)
            obj.select_set(state=True)
            bpy.ops.export_scene.obj(filepath=f"{self.obj_export_path}{tmp_obj_struct.mesh_name}.obj",
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
        else:
            print(f"{C_YELLOW}Mesh already exported{C_RESET}")

        tmp_obj_struct.rot = [obj.rotation_euler[0], obj.rotation_euler[1], obj.rotation_euler[2]]
        tmp_obj_struct.size = [obj.dimensions[0], obj.dimensions[1], obj.dimensions[2]]

    def get_parsed_scene(self):
        for obj in bpy.data.objects:
            print(f"{C_GREEN}{'-'*25} Exporting {obj.name}{C_RESET}")
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
                print(f"{C_RED}Unknown obj type: {obj.type}{C_RESET}")

            self.final_dict[tmp_obj_struct.name] = tmp_obj_struct.serialize()
            print('')
        return self.final_dict

    def create_tex_from_color(self, color):
        name = f"{color[0]}_{color[1]}_{color[2]}.bmp"
        bfType = 19778  # Bitmap signature
        bfReserved1 = 0
        bfReserved2 = 0
        bcPlanes = 1
        bcSize = 12
        bcBitCount = 24
        bfOffBits = 26
        bfSize = 26+1*3*1

        with open(self.tex_export_path + name, 'wb') as f:
            f.write(pack('<HLHHL',
                    bfType,
                    bfSize,
                    bfReserved1,
                    bfReserved2,
                    bfOffBits))  # Writing BITMAPFILEHEADER
            f.write(pack('<LHHHH',
                    bcSize,
                    1,
                    1,
                    bcPlanes,
                    bcBitCount))  # Writing BITMAPINFO
            f.write(pack('<BBB', *color))
            for i in range (4 - ((1*3) % 4) % 4):
                f.write(pack('B', 0))
        return name


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


if __name__ == '__main__':
    level_name = input("\n\nEnter map name: ")
    print(f"{C_BLUE}{'-'*50} Starting export{C_RESET}")

    scene_parser = SceneParser(level_name)
    scene_parser.init()
    scene = scene_parser.get_parsed_scene()

    with open(f"{EXPORT_PATH}/{level_name}/{level_name}.json", 'w', encoding="utf-8") as f:
        f.write(json.dumps(scene))

    print(f"{C_BLUE}{'-'*50} Export done!{C_RESET}")
