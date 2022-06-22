import platform
import subprocess

if __name__ == "__main__":
  if platform.system() == "Windows":
    subprocess.call("cmake -B build -G \"Visual Studio 16 2019\"")
  else:
    print("Error: Unsupported operating system!")
