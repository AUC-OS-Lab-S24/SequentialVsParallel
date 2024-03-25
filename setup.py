# due to the nature of fixed_nproc directory we cannot push it to github
# thus it is ignored and must be setup by this script

import os


os.makedirs('fixed_nproc', exist_ok=True);

print("Created fixed_nproc successfully, run command to populate it with random files to compute!")