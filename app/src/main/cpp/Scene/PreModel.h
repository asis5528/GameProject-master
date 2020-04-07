//
// Created by sergio on 3/27/2020.
//

#ifndef MY_APPLICATION_PREMODEL_H
#define MY_APPLICATION_PREMODEL_H

class PreModel{
public:
    std::vector<Object> objects;
    PreModel(){


        ObjectInit terrain = ObjectInit("terrain.obj","Shaders/terrain.vert","Shaders/terrain.frag","terrain.png");
        objects.push_back(terrain.object);
        ObjectInit tree = ObjectInit("tree.obj","Shaders/terrain.vert","Shaders/simple.frag","tree.png");
        objects.push_back(tree.object);

        ObjectInit bill = ObjectInit("bill.obj","Shaders/tree.vert","Shaders/tree.frag","billBoard.png");
        objects.push_back(bill.object);

        ObjectInit cube = ObjectInit("cube.obj","Shaders/simple.vert","Shaders/cubemap.frag");
        objects.push_back(cube.object);

        ObjectInit model = ObjectInit("model.obj","Shaders/pbr.vert","Shaders/pbr.frag");
        objects.push_back(model.object);
    }

};

#endif //MY_APPLICATION_PREMODEL_H
