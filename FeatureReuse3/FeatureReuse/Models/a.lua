-- Lua script.
p=tetview:new()
p:load_stl("G:/develop/c++Projects/STLViewer/Models/ϴ����ӷ��㣬���ʣ�1.stl")
rnd=glvCreate(0, 0, 500, 500, "TetView")
p:plot(rnd)
glvWait()
