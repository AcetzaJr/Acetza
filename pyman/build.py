import subprocess


def build(config: str) -> int:
    return subprocess.run(
        [
            "cmake",
            "--build",
            "build",
            "--config",
            config,
            "--target",
            "Muza",
            "--parallel",
            "16",
        ]
    ).returncode
