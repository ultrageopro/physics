import physics
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation, FFMpegWriter
import numpy as np
from tqdm import tqdm

sun = physics.Object(
    physics.Mass(1.98847e30),
    physics.Vector3Length([physics.Length(0), physics.Length(0), physics.Length(0)]),
    physics.Vector3Speed([physics.Speed(0), physics.Speed(0), physics.Speed(0)]),
)

earth = physics.Object(
    physics.Mass(5.9722e24),
    physics.Vector3Length([physics.Length(1.496e11), physics.Length(0), physics.Length(0)]),
    physics.Vector3Speed([physics.Speed(0), physics.Speed(29780), physics.Speed(0)]),
)

asteroid = physics.Object(
    physics.Mass(1e12),
    physics.Vector3Length(
        [
            physics.Length(-4.5e11),
            physics.Length(1.0e10),
            physics.Length(0),
        ]
    ),
    physics.Vector3Speed(
        [
            physics.Speed(45000),
            physics.Speed(-5000),
            physics.Speed(0),
        ]
    ),
)

sim = physics.Simulator([sun, earth, asteroid], physics.Length(1e7))

dt = physics.Time(60 * 60)
steps = 365 * 24

earth_xs, earth_ys = [], []
ast_xs, ast_ys = [], []

for _ in tqdm(range(steps)):
    sim.step(dt)
    e = sim.objects()[1]
    a = sim.objects()[2]
    earth_xs.append(e.position[0].value)
    earth_ys.append(e.position[1].value)
    ast_xs.append(a.position[0].value)
    ast_ys.append(a.position[1].value)

earth_xs = np.array(earth_xs) / 1e9
earth_ys = np.array(earth_ys) / 1e9
ast_xs = np.array(ast_xs) / 1e9
ast_ys = np.array(ast_ys) / 1e9

fig, ax = plt.subplots(figsize=(8, 8))
ax.set_facecolor("black")
ax.set_aspect("equal")
ax.set_xlabel("X (million km)", color="white")
ax.set_ylabel("Y (million km)", color="white")
ax.set_title("Earth–Asteroid Flyby Simulation", color="white")
ax.tick_params(colors="white")

max_range = max(np.max(np.abs(earth_xs)), np.max(np.abs(earth_ys)))
ax.set_xlim(-max_range * 1.3, max_range * 1.3)
ax.set_ylim(-max_range * 1.3, max_range * 1.3)

np.random.seed(123)
stars_x = np.random.uniform(-max_range * 1.3, max_range * 1.3, 3000)
stars_y = np.random.uniform(-max_range * 1.3, max_range * 1.3, 3000)
stars_alpha = np.random.uniform(0.15, 0.5, 3000)
ax.scatter(stars_x, stars_y, s=1, c="white", alpha=stars_alpha, zorder=0)

ax.scatter([0], [0], color="yellow", s=350, edgecolors="orange", linewidths=2, zorder=3)

(earth_point,) = ax.plot([], [], "o", color="#00aaff", markersize=6, zorder=4)
(earth_trail,) = ax.plot([], [], "-", color="#00ccff", linewidth=1.4, alpha=0.6, zorder=2)

(asteroid_point,) = ax.plot([], [], "o", color="red", markersize=3, zorder=6)
(asteroid_trail,) = ax.plot([], [], "-", color="red", linewidth=1.0, alpha=0.6, zorder=2)

day_text = ax.text(0.02, 0.95, "", transform=ax.transAxes, fontsize=12, color="white")


def frame_to_day(f):
    return f / 24


def update(frame):
    earth_point.set_data([earth_xs[frame]], [earth_ys[frame]])
    earth_trail.set_data(earth_xs[:frame], earth_ys[:frame])
    asteroid_point.set_data([ast_xs[frame]], [ast_ys[frame]])
    asteroid_trail.set_data(ast_xs[:frame], ast_ys[:frame])
    day_text.set_text(f"Day {frame_to_day(frame):.1f}")

    return earth_point, earth_trail, asteroid_point, asteroid_trail, day_text


anim = FuncAnimation(
    fig,
    update,
    frames=len(earth_xs),
    interval=8,
    blit=True,
)

writer = FFMpegWriter(fps=60, bitrate=5000)
anim.save("orbit.mp4", writer=writer)

print("Saved orbit.mp4")
