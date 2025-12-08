import physics

print("OK: physics imported!")
print(dir(physics))

obj = physics.Object(physics.Mass(5.0))
print("Object OK:", obj.speed)

v = physics.Vector3d([1, 2, 3])
print(v)
