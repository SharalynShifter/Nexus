#!/usr/bin/python
import math
import libtcodpy as libtcod
# size of the heightmap
HM_WIDTH=100
HM_HEIGHT=80
rnd=libtcod.random_new_from_seed(3735928559)
noise=libtcod.noise_new(2,libtcod.NOISE_DEFAULT_HURST,libtcod.NOISE_DEFAULT_LACUNARITY,rnd)
# 3x3 kernel for smoothing operations
smoothKernelSize=9
smoothKernelDx=[-1,0,1,-1,0,1,-1,0,1]
smoothKernelDy=[-1,-1,-1,0,0,0,1,1,1]
smoothKernelWeight=[1.0,2.0,1.0,2.0,20.0,2.0,1.0,2.0,1.0]
# function building the heightmap
def buildMap(hm) :
    libtcod.heightmap_normalize(hm,0,1)
    libtcod.heightmap_scale_fbm(hm,noise,1,1,0,0,6,0.5,1)
    scaleFbmDelta += HM_WIDTH
    smoothKernelWeight[4] = 20
    for i in range(2,-1,-1) :
        libtcod.heightmap_kernel_transform(hm,smoothKernelSize,smoothKernelDx,smoothKernelDy,smoothKernelWeight,0,0)
    tmp=libtcod.heightmap_new(HM_WIDTH,HM_HEIGHT)
    libtcod.heightmap_add_fbm(tmp,noise,1,1,0,0,6,1,1)
    libtcod.heightmap_lerp(hm,tmp,hm,0)
    libtcod.heightmap_delete(tmp)
# test code to print the heightmap
hm=libtcod.heightmap_new(HM_WIDTH,HM_HEIGHT)
buildMap(hm)
libtcod.console_init_root(HM_WIDTH,HM_HEIGHT,"height map test",False)
for x in range(HM_WIDTH) :
    for y in range(HM_HEIGHT) :
        z = libtcod.heightmap_get_value(hm,x,y)
        val=int(z*255) & 0xFF
        c=libtcod.Color(val,val,val)
        libtcod.console_set_char_background(None,x,y,c,libtcod.BKGND_SET)
libtcod.console_flush()
libtcod.console_wait_for_keypress(True)
