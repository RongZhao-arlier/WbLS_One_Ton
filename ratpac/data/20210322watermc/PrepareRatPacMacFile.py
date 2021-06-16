import os
import sys

thisfile = open(sys.argv[1],'w')

thisfile.write('/rat/db/set DETECTOR experiment "20210322watermc"\n')
thisfile.write('/rat/db/set DETECTOR geo_file "20210322watermc/tophodo_top.geo"\n')
thisfile.write('/rat/db/set DAQ noise_flag 0\n')

thisfile.write('#/random/setSeeds 1000 1000\n')

thisfile.write('/PhysicsList/setOpWLS g4\n')

thisfile.write('/run/initialize\n')

thisfile.write('/tracking/storeTrajectory 0\n')
thisfile.write('/tracking/storeParticleTrajectory nu_e\n')
thisfile.write('/tracking/storeParticleTrajectory anti_nu_e\n')
thisfile.write('/tracking/storeParticleTrajectory nu_mu\n')
thisfile.write('/tracking/storeParticleTrajectory anti_nu_mu\n')
#thisfile.write('/tracking/storeMuonTrajectorySpecial Decay true\n')
#thisfile.write('/tracking/storeMuonTrajectorySpecial muMinusCaptureAtRest true\n')

thisfile.write('# BEGIN EVENT LOOP\n')
thisfile.write('/rat/proc simpledaq\n')
thisfile.write('/rat/proc count\n')
thisfile.write('/rat/procset update 1\n')

thisfile.write('/rat/proc fitcentroid\n')

thisfile.write('#/rat/proc prune\n')
thisfile.write('#/rat/procset prune "mc.track:opticalphoton"\n')

thisfile.write('/rat/proclast outroot\n')
thisfile.write('/rat/procset file "')
thisfile.write(sys.argv[2])
thisfile.write('"\n')

thisfile.write('/generator/add external external:poisson: "')
thisfile.write(sys.argv[3])
thisfile.write('" \n')

thisfile.write('#/run/verbose 2\n')
thisfile.write('#/event/verbose 3\n')
thisfile.write('#/tracking/verbose 2\n')

thisfile.write('/run/beamOn 7000\n')#beam number
