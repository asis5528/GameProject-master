//
// Created by sergio on 3/27/2020.
//

#ifndef MY_APPLICATION_PREMODEL_H
#define MY_APPLICATION_PREMODEL_H

class PreModel{
public:
    std::vector<Object> objects;
    PreModel(){
        ObjectInit balcony_floor  = ObjectInit("balcony_floor.obj","Shaders/pbr.vert","Shaders/pbr.frag");
        objects.push_back(balcony_floor.object);

        ObjectInit ceiling = ObjectInit("ceiling.obj","Shaders/pbr.vert","Shaders/pbr.frag");
        objects.push_back(ceiling.object);

        ObjectInit door_left = ObjectInit("door_left.obj","Shaders/pbr.vert","Shaders/pbr.frag");
        objects.push_back(door_left.object);

        ObjectInit door_right = ObjectInit("door_right.obj","Shaders/pbr.vert","Shaders/pbr.frag");
        objects.push_back(door_right.object);

        ObjectInit pillar = ObjectInit("pillar.obj","Shaders/pbr.vert","Shaders/pbr.frag");
        objects.push_back(pillar.object);

        ObjectInit pillar_top = ObjectInit("pillar_top.obj","Shaders/pbr.vert","Shaders/pbr.frag");
        objects.push_back(pillar_top.object);

        ObjectInit room = ObjectInit("room.obj","Shaders/pbr.vert","Shaders/pbr.frag");
        objects.push_back(room.object);

        ObjectInit cube = ObjectInit("cube.obj","Shaders/simple.vert","Shaders/cubemap.frag");
        objects.push_back(cube.object);
    }

};

#endif //MY_APPLICATION_PREMODEL_H
