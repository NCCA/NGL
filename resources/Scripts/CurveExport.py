import maya.OpenMaya as OM
import maya.OpenMayaAnim as OMA
import maya.cmds as cmds


def ExportCurvesToOpenGLCamera(fname,eyeCurve,lookCurve) :
	# get the control points of both the curves

	EyePoints = cmds.xform( (eyeCurve+ ".cv[*]"), q=True, ws=True, t=True,os=True )
	LookPoints = cmds.xform( (lookCurve+ ".cv[*]"), q=True, ws=True, t=True,os=True )

	# open the file
	ofile=open(fname,'w')
	#write out the number of cp in each curve
	ofile.write("%d %d\n" %( len(EyePoints)/3 ,len(LookPoints)/3) )
	# get curve Transformaiton matrix values

	for n in range(0,len(EyePoints),3) :
		# write to the file
		ofile.write("%f %f %f \n" %(EyePoints[n],EyePoints[n+1],EyePoints[n+2]))

	for n in range(0,len(LookPoints),3) :
		ofile.write("%f %f %f \n" %(LookPoints[n],LookPoints[n+1],LookPoints[n+2]))



ExportCurvesToOpenGLCamera("/Users/jmacey/Cam.txt","curve2","curve1")