import physics
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation, FFMpegWriter
from matplotlib.patches import Circle, Rectangle

ball_mass = physics.Mass(0.17)
ball_radius = 0.057
collision_distance = physics.Length(2 * ball_radius)


ball1 = physics.Object(
    ball_mass,
    physics.Vector3Length([physics.Length(-0.6), physics.Length(0), physics.Length(0)]),
    physics.Vector3Speed([physics.Speed(1.5), physics.Speed(0), physics.Speed(0)]),
)

ball2 = physics.Object(
    ball_mass,
    physics.Vector3Length([physics.Length(0.6), physics.Length(-0.3), physics.Length(0)]),
    physics.Vector3Speed([physics.Speed(-0.5), physics.Speed(0.5), physics.Speed(0)]),
)

ball3 = physics.Object(
    ball_mass,
    physics.Vector3Length([physics.Length(0), physics.Length(0.4), physics.Length(0)]),
    physics.Vector3Speed([physics.Speed(0), physics.Speed(-1.0), physics.Speed(0)]),
)

sim = physics.Simulator([ball1, ball2, ball3], collision_distance)
sim.enable_gravity(False)

dt = physics.Time(0.005)
steps = 500


b1, b2, b3 = [], [], []

for _ in range(steps):
    sim.step(dt)
    o1, o2, o3 = sim.objects()

    b1.append((o1.position[0].value, o1.position[1].value))
    b2.append((o2.position[0].value, o2.position[1].value))
    b3.append((o3.position[0].value, o3.position[1].value))

b1 = np.array(b1)
b2 = np.array(b2)
b3 = np.array(b3)

fig, ax = plt.subplots(figsize=(7, 7))
ax.set_aspect("equal")
ax.set_facecolor("black")

ax.set_xlabel("X (m)", color="white")
ax.set_ylabel("Y (m)", color="white")
ax.set_title("2D Three-ball Collision Simulation", color="white")
ax.tick_params(colors="white")

ax.set_xlim(-1.0, 1.0)
ax.set_ylim(-1.0, 1.0)

table = Rectangle((-1.0, -1.0), 2.0, 2.0, fill=False, edgecolor="#444", linewidth=2)
ax.add_patch(table)

ball1_patch = Circle((0, 0), ball_radius, color="#1f77b4")
ball2_patch = Circle((0, 0), ball_radius, color="#ff7f0e")
ball3_patch = Circle((0, 0), ball_radius, color="#2ca02c")

for p in [ball1_patch, ball2_patch, ball3_patch]:
    ax.add_patch(p)

(trail1,) = ax.plot([], [], "-", color="#1f77b4", alpha=0.4, linewidth=1.5)
(trail2,) = ax.plot([], [], "-", color="#ff7f0e", alpha=0.4, linewidth=1.5)
(trail3,) = ax.plot([], [], "-", color="#2ca02c", alpha=0.4, linewidth=1.5)

time_text = ax.text(0.02, 0.95, "", transform=ax.transAxes, fontsize=12, color="white")


def update(i):
    ball1_patch.center = b1[i]
    ball2_patch.center = b2[i]
    ball3_patch.center = b3[i]

    trail1.set_data(b1[:i, 0], b1[:i, 1])
    trail2.set_data(b2[:i, 0], b2[:i, 1])
    trail3.set_data(b3[:i, 0], b3[:i, 1])

    time_text.set_text(f"t = {i * dt.value:.3f} s")

    return (ball1_patch, ball2_patch, ball3_patch, trail1, trail2, trail3, time_text)


anim = FuncAnimation(fig, update, frames=steps, interval=15, blit=True)

writer = FFMpegWriter(fps=60, bitrate=5000)
anim.save("three_balls.mp4", writer=writer)

print("Saved 2D simulation as three_balls.mp4")
