# -*- coding: utf-8 -*-
"""
Created on Tue Oct 22 11:54:05 2024

@author: lenovo
"""

from skyfield.api import Topos, load
from skyfield.api import wgs84
from datetime import datetime
from skyfield.api import Loader
from skyfield.api import utc
import numpy as np
# 加载天体数据
ts = load.timescale()
au = 149597870700
#load = Loader(get_skyfield_data_path())
eph = load('de421.bsp')

# 定义一个函数来获取行星的位置和速度
def get_planet_data(planet_name, date):
    # 创建一个时间对象
    
    t = ts.from_datetime(date)
    
    # 太阳的位置和速度
    sun = eph['sun']
    
    # 行星的位置和速度
    planet = eph[planet_name]
    
    # 地球表面某点的位置
 #   earth_position = wgs84.itrf_to_geodetic(wgs84.earth(t))
    
    # 计算太阳和行星相对于地球的位置
    sun_position = sun.at(t).position.au*au
    planet_position = planet.at(t).position.au*au
    relative_position = planet_position - sun_position
    
    # 计算速度
    sun_velocity = sun.at(t).velocity.km_per_s*1000
    planet_velocity = planet.at(t).velocity.km_per_s*1000
    
    # 将速度转换为米/秒
    sun_velocity = list(sun_velocity)
    planet_velocity = list(planet_velocity)
    
    return {
        'name': planet_name,
        'position': planet_position,
        'velocity': planet_velocity,
        
    }

# 获取当前时间
now = datetime.utcnow()
now = now.replace(tzinfo=utc) 
# 太阳系行星列表
planets = ['sun', 'mercury', 'venus', 'earth','moon', 'mars', 'jupiter BARYCENTER', 'saturn BARYCENTER', 'uranus BARYCENTER', 'neptune BARYCENTER']
mass=[1.989e30   ,     3.301e23   ,     4.867e24   ,     5.972e24   ,     7.34767309e22  , 6.417e23   ,     1.899e27  ,      5.683e26     ,   8.682e25    ,    1.024e26       ];
diam=[1.3914e9   ,   4.879e6   ,    1.0821e7     , 1.2756e7   ,   3.4748e6   ,   6.779e6  ,     1.4298e7  ,    1.2041e7  ,    5.153e7     ,  4.955e7      ];
# 创建一个列表来存储所有行星的数据
solar_system_data = []

for planet in planets:
    data = get_planet_data(planet, now)
    solar_system_data.append(data)

# 打印结果
i=0;print(len(planets));
for data in solar_system_data:
    #print(f"Planet: {data['name']}")
    #print(f"Position (AU): {data['position']}")
    #print(f"Velocity (km/s): {data['velocity']}")
    print(f"{data['position'][0]} {data['position'][1]} {data['position'][2]} {mass[i]} {diam[i]} {data['velocity'][0]} {data['velocity'][1]} {data['velocity'][2]} {i} {planets[i]}")
#    if i<len(planets)-1:
#        print(solar_system_data[i]['position'],solar_system_data[i+1]['position'])
#        print(solar_system_data[i]['position']-solar_system_data[i+1]['position'])
#        print(np.sqrt(np.dot(solar_system_data[i]['position']-solar_system_data[i+1]['position'],solar_system_data[i]['position']-solar_system_data[i+1]['position'])))
    i=i+1;