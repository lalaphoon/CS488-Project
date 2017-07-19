--Define the materail colors
water = gr.material({0.1,0.2,0.7},{0.99,0.99,0.99},99, 1,3)
white = gr.material({200.0,200.0,200.0},{0.99,0.99,0.99},99,1,2)


rootNode = gr.node('root')

sun = gr.mesh('sphere','sun')
--rootNode:add_child(sun)
sun:set_material(white)
sun:scale(1.5,1.5,1.5)
--sun:translate(15.0,8.0,-15.0)
sun:translate(0.0, 8.0, -15.0)



water_plane = gr.mesh('water', 'plane')
water_plane:scale(200.0, 200.0, 200.0)
water_plane:translate(0.0, -0.7, 0.0)
water_plane:set_material(gr.material({0.8, 0.2, 0.2}, {0.8, 0.8, 0.8}, 10.0))
rootNode:add_child(water_plane)

lake = gr.mesh('water', 'lake')
lake:scale(100.0, 100.0, 100.0)
lake:translate(0.0, -0.7, 0.0)
lake:set_material(gr.material({0.8, 0.2, 0.2}, {0.8, 0.8, 0.8}, 10.0))
rootNode:add_child(lake)


sphereMesh = gr.mesh('sphere', 'player')
sphereMesh:scale(0.7, 0.7, 0.7)
sphereMesh:translate(0.0, -0.0, -5.0)
sphereMesh:set_material(gr.material({0.4, 0.4, 0.8}, {0.8, 0.8, 0.8}, 50.0))
rootNode:add_child(sphereMesh)



mazeMesh = gr.mesh('maze', 'house')
mazeMesh:scale(1.5, 1.5, 1.5)
mazeMesh:translate(0.0, -1.0, -9.0)
mazeMesh:set_material(gr.material({0.4, 0.4, 0.8}, {0.8, 0.8, 0.8}, 50.0))
--rootNode:add_child(mazeMesh)

eggMesh = gr.mesh('egg', 'egg')
eggMesh:scale(0.7, 0.7, 0.7)
eggMesh:translate(0.0, -0.8, 15.0)
eggMesh:set_material(white)
rootNode:add_child(eggMesh)


egg1 = gr.mesh('egg', 'egg1')
egg1:scale(0.7, 0.7, 0.7)
egg1:translate(-9.0, -0.8, 18.0)
egg1:set_material(white)
rootNode:add_child(egg1)

egg2 = gr.mesh('egg', 'egg2')
egg2:scale(0.7, 0.7, 0.7)
egg2:translate(7.0, -0.8, 21.0)
egg2:set_material(white)
rootNode:add_child(egg2)

turtle = gr.mesh('turtle', 'turtle')
--turtle:translate(10.0, -0.8, 5.0)
turtle:scale(3.0, 3.0, 3.0)
turtle:rotate('y', -35.0)
turtle:translate(5.0, -0.8, 5.0)
turtle:set_material(white)
rootNode:add_child(turtle)


turtle1 = gr.mesh('turtle', 'turtle1')
turtle1:scale(3.0, 3.0, 3.0)
turtle1:rotate('y', -35.0)
turtle1:translate(5.0, -0.8, 0.0)
turtle1:set_material(white)
rootNode:add_child(turtle1)


turtle2 = gr.mesh('turtle', 'turtle2')
turtle2:scale(3.0, 3.0, 3.0)
turtle2:rotate('y', -35.0)
turtle2:translate(-5.0, -0.8, 5.0)
turtle2:set_material(white)
rootNode:add_child(turtle2)



tree = gr.mesh('tree', 'tree')
tree:scale(3.0, 3.0, 3.0)
tree:translate(20.0, -0.8, -8.0)
tree:set_material(white)
rootNode:add_child(tree)

tree1 = gr.mesh('tree', 'tree1')
tree1:scale(3.0, 3.0, 3.0)
tree1:translate(25.0, -0.8, -43.0)
tree1:set_material(white)
rootNode:add_child(tree1)

tree2 = gr.mesh('tree', 'tree2')
tree2:scale(3.0, 3.0, 3.0)
tree2:translate(-20.0, -0.8, -35.0)
tree2:set_material(white)
rootNode:add_child(tree2)

tree3 = gr.mesh('tree', 'tree3')
tree3:scale(3.0, 3.0, 3.0)
tree3:translate(-20.0, -0.8, 30.0)
tree3:set_material(white)
rootNode:add_child(tree3)


house1 = gr.mesh('house', 'house1')
house1:scale(5.0, 5.0, 5.0)
house1:translate(-4.0, -0.8, -10.0)
house1:set_material(white)
rootNode:add_child(house1)



-- Return the root with all of it's childern.  The SceneNode A3::m_rootNode will be set
-- equal to the return value from this Lua script.
return rootNode