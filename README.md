# How to use

**1. Download**
  ```
  git clone git@github.com:SejunKang/babel.git
  ```

**2. Operate `CMAKE` to create the executable file**
After downloading the file, create `build` directory and move into it.

```
cd babel
mkdir build
cd build
```

Type `ccmake ..` and set the `CLHEP` path to `/program/clhep/2.4.7.1/lib/CLHEP-2.4.7.1`. Then press `c` multiple times until `[g] generate` button appears in the Keys window.

Press `g` to confirm the CMAKE settings.

Once the settings are ready, type the following commands to create the executable file `babel`.

```
cmake ..
make
```

**3. Run the simulation**

a. Run in UI mode

```
./babel
```

Push the green start button on the top of the GUI screen to shoot one muon beam. If you want to shoot multiple beams, type `/run/beamOn <number>` in the UI window.

(Not recommended because I refined the beam shooting logic, which became quite complicated.) 

b. Run in batch mode (Horizontal)

Since running the simulation directly in the masterserver makes the server slower, I made two script files to run the program in node servers using `slurm`. To shoot the beam horizontally, use `noderun_hor.sh`.

```
sbatch --nodelist=node01 noderun_hor.sh
or
sbatch --nodelist=node02 noderun_hor.sh
```

This will automatically run the simulation without any graphic visualization. To change the number of beams, open `run_hor.mac` and change the number in the line `/run/beamOn <number>`. You must do `make` in the `build` directory after changing this.

Once the simulation is done, the output ROOT file `output_hor.root` will be generated.

c. Run in batch mode (Vertical)

Vertical incidence is run for 15 different positions on the scintillator: -70 cm, -60 cm, -50 cm, -40 cm, -30 cm, -20 cm, -10 cm, 0 cm, 10 cm, 20 cm, 30 cm, 40 cm, 50 cm, 60 cm, 70 cm. Here, the center of the scintillator bar is placed on the origin (0 cm).

Using `noderun_ver.sh`, the simulation automatically runs the 15 different positions sequentially.

```
sbatch --nodelist=node01 noderun_ver.sh
or
sbatch --nodelist=node02 noderun_ver.sh
```

Once the simulation is done, the output ROOT file `output_ver.root` will be generated. To change the number of beams, open `run_ver_all.sh` and change the number in the line `num=1000`. You don't have to do `make` in this case.

**4. Analysis**

By operating the ROOT code `Addup.cc`, you can count the number of photons that reached the PMT for all beam positions.

Also, their Horizontal/Vertical ratios are calculated. I also included graphing process.

**5. Other important factors**
- If you modify anything of the codes in `src`, `include`, or the outermost directory, you must move to the `build` directory and do `make`.
- If you make a new `.cc` or `.hh` file in `src` or `include`, or delete the existing files, you must do `cmake ..` before `make` in the `build` directory.
- If there are any problems while running `cmake`, type `ccmake ..` in the `/build` directory and check if all the environment variables are correctly registered. You must also register your Geant4 path in `.bashrc`.
- `Geant4` path for our masterserver is `/program/geant4/11.3.2/bin/geant4.sh`.
- **Please call me if any other problems happen.** 
