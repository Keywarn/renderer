from shutil import copyfile
mode = "global"
for i in range (30):
  src = mode + str(29-i).zfill(3) + ".ppm"
  dst = mode + str(74+i).zfill(3) + ".ppm"
  copyfile(src, dst)
