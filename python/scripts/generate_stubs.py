import os
import shutil
import pybind11_stubgen

root_dir = os.path.dirname(os.path.dirname(__file__))
project_dir = os.path.dirname(root_dir)
pkg_dir = os.path.join(root_dir, "physics")
so_dst = os.path.join(pkg_dir, "_core.so")

build_bindings = os.path.join(project_dir, "build", "bindings")
so_candidates = [
    f for f in os.listdir(build_bindings) if f.startswith("_core") and f.endswith(".so")
]

if not so_candidates:
    raise RuntimeError("Cannot find built _core.so in build/bindings")

so_src = os.path.join(build_bindings, so_candidates[0])

shutil.copyfile(so_src, so_dst)
pybind11_stubgen.main(
    [
        "physics._core",
        "-o",
        root_dir,
    ]
)
