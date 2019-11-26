import hoomd
import hoomd.hpmc
import numpy as np
import hoomd.hpmc._hpmc as _hpmc

from hoomd import hpmc

def test_convex_polyhedron():

    args_1 = {'vertices':[(0, 5, 0), (1, 1, 1), (1, 0, 1), (0, 1, 1), (1, 1, 0), (0, 0, 1)], 'ignore_statistics':1}
    test_convex_polyhedron1 = _hpmc.poly3d_verts(args_1)
    test_dict1 = test_convex_polyhedron1.asDict()
    assert test_dict1 == args_1
    
    args_2 = {'vertices':[(1, 0, 0), (1, 1, 0), (1, 2, 1), (0, 1, 1), (1, 1, 2), (0, 0, 1)], 'ignore_statistics':0}
    test_convex_polyhedron2 = _hpmc.poly3d_verts(args_2)
    test_dict2 = test_convex_polyhedron2.asDict()
    assert test_dict2 == args_2
    
    args_3 = {'vertices':[(0, 0, 0), (1, 1, 1), (1, 0, 2), (2, 1, 1)], 'ignore_statistics':1}
    test_convex_polyhedron3 = _hpmc.poly3d_verts(args_3)
    test_dict3 = test_convex_polyhedron3.asDict()
    assert test_dict3 == args_3
    
    args_4 = {'vertices':[(0, 1, 0), (1, 1, 1), (1, 0, 1), (0, 1, 1), (1, 1, 0), (0, 0, 1), (0, 0, 1), (0, 0, 1)], 'ignore_statistics':0}
    test_convex_polyhedron4 = _hpmc.poly3d_verts(args_4)
    test_dict4 = test_convex_polyhedron4.asDict()
    assert test_dict4 == args_4
    
    args_5 = {'vertices':[(0, 10, 3), (3, 2, 1), (1, 2, 1), (0, 1, 1), (1, 1, 0), (5, 0, 1), (0, 10, 1), (9, 5, 1), (0, 0, 1)], 'ignore_statistics':1}
    test_convex_polyhedron5 = _hpmc.poly3d_verts(args_5)
    test_dict5 = test_convex_polyhedron5.asDict()
    assert test_dict5 == args_5
    

# these tests are for the python side
def test_convex_polyhedron_python():

    verts = [(-1, 1, 0), (1, 0, -1), (1, 1, 1), (-1, -1, 1)] 
    poly = hpmc.integrate.ConvexPolyhedron(23456)
    poly.shape['A'] = dict(vertices=verts)
    assert not poly.shape['A']['ignore_statistics']
    np.testing.assert_allclose(poly.shape['A']['vertices'], verts)

def test_convex_polyhedron_after_attaching(device, dummy_simulation):

    verts = [(-1, 1, 0), (1, 0, -1), (1, 1, 1), (-1, -1, 1)] 
    verts2 = [(-1, 1, 1), (1, -1, 0), (1, 1, 1)] 
    poly = hpmc.integrate.ConvexPolyhedron(23456)
    poly.shape['A'] = dict(vertices=verts)
    poly.shape['B'] = dict(vertices=verts2, ignore_statistics=True)

    sim = dummy_simulation
    sim.operations.add(poly)
    sim.operations.schedule()

    assert not poly.shape['A']['ignore_statistics']
    assert poly.shape['B']['ignore_statistics']
    np.testing.assert_allclose(poly.shape['A']['vertices'], verts)    
    np.testing.assert_allclose(poly.shape['B']['vertices'], verts2)  
