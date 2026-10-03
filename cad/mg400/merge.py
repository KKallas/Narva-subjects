import struct, math, xml.etree.ElementTree as ET

root = ET.parse('mg400.urdf').getroot()

def rpy_mat(r,p,y):
    cr,sr=math.cos(r),math.sin(r); cp,sp=math.cos(p),math.sin(p); cy,sy=math.cos(y),math.sin(y)
    return [[cy*cp, cy*sp*sr-sy*cr, cy*sp*cr+sy*sr],
            [sy*cp, sy*sp*sr+cy*cr, sy*sp*cr-cy*sr],
            [-sp,   cp*sr,          cp*cr]]

def mul(A,B):
    RA,tA=A; RB,tB=B
    R=[[sum(RA[i][k]*RB[k][j] for k in range(3)) for j in range(3)] for i in range(3)]
    t=[sum(RA[i][k]*tB[k] for k in range(3))+tA[i] for i in range(3)]
    return (R,t)

def apply(T,v):
    R,t=T
    return [sum(R[i][k]*v[k] for k in range(3))+t[i] for i in range(3)]

I=([[1,0,0],[0,1,0],[0,0,1]],[0,0,0])

joints=[]
for j in root.findall('joint'):
    o=j.find('origin')
    xyz=[0,0,0]; rpy=[0,0,0]
    if o is not None:
        xyz=[float(x) for x in o.get('xyz','0 0 0').split()]
        rpy=[float(x) for x in o.get('rpy','0 0 0').split()]
    joints.append((j.find('parent').get('link'), j.find('child').get('link'), (rpy_mat(*rpy), xyz)))

# forward kinematics, all joint angles = 0
poses={'base_link': I}
changed=True
while changed:
    changed=False
    for p,c,T in joints:
        if p in poses and c not in poses:
            poses[c]=mul(poses[p],T); changed=True

meshes={}
for l in root.findall('link'):
    v=l.find('visual')
    if v is None: continue
    m=v.find('geometry/mesh')
    if m is None: continue
    meshes[l.get('name')]=m.get('filename').split('/')[-1]

tris=[]
SCALE=1000.0  # m -> mm
for link,fn in meshes.items():
    T=poses.get(link)
    if T is None:
        print('no pose for', link); continue
    with open(fn,'rb') as f:
        f.read(80)
        n=struct.unpack('<I', f.read(4))[0]
        for _ in range(n):
            d=struct.unpack('<12fH', f.read(50))
            nv=apply((T[0],[0,0,0]), d[0:3])
            vs=[apply(T, d[3:6]), apply(T, d[6:9]), apply(T, d[9:12])]
            tris.append((nv, vs))
    print(f'{link:10s} {fn:16s} {n:6d} tris  origin={[round(x*SCALE,1) for x in T[1]]}')

with open('MG400_assembled_mm.stl','wb') as f:
    f.write(b'Dobot MG400 assembled from MG400_ROS meshes, units mm, all joints 0'.ljust(80,b' '))
    f.write(struct.pack('<I', len(tris)))
    for nv,vs in tris:
        f.write(struct.pack('<3f', *nv))
        for v in vs:
            f.write(struct.pack('<3f', *[x*SCALE for x in v]))
        f.write(struct.pack('<H',0))

xs=[v[0]*SCALE for _,vs in tris for v in vs]
ys=[v[1]*SCALE for _,vs in tris for v in vs]
zs=[v[2]*SCALE for _,vs in tris for v in vs]
print(f'\ntotal {len(tris)} triangles')
print(f'bbox mm  X {min(xs):8.1f} .. {max(xs):8.1f}   Y {min(ys):8.1f} .. {max(ys):8.1f}   Z {min(zs):8.1f} .. {max(zs):8.1f}')
