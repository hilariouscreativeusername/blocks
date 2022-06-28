import platform
import subprocess

if __name__ == "__main__":
  if platform.system() == "Windows":
    subprocess.call("cmake -B build -G \"Visual Studio 16 2019\"")
  elif platform.system() == "Darwin":
    subprocess.call("cmake -B build -G \"Xcode\"", shell=True)
  elif platform.system() == "Linux":
    subprocess.call("cmake -B build -G \"Unix Makefiles\"")
  else:
    print("Error: Unsupported operating system! \"", platform.system(), "\"")
