// Copyright 2019 Rokoko Electronics. All Rights Reserved.

#include "VirtualProductionSource.h"

FVirtualProductionSource* FVirtualProductionSource::instance = 0;

void FVirtualProductionSource::ReceiveClient(ILiveLinkClient* InClient, FGuid InSourceGuid)
{
	Client = InClient;
	SourceGuid = InSourceGuid;
	instance = this;
}

bool FVirtualProductionSource::IsSourceStillValid()
{
	return true;
}

void FVirtualProductionSource::HandleClearSubject(const FName subjectName)
{
	Client->ClearSubject(subjectName);
}

void FVirtualProductionSource::ClearAllSubjects() {
	for (int i = 0; i < subjectNames.Num(); i++) {
		HandleClearSubject(subjectNames[i]);
	}
	for (int i = 0; i < faceNames.Num(); i++) {
		HandleClearSubject(faceNames[i]);
	}
	for (int i = 0; i < suitNames.Num(); i++) {
		HandleClearSubject(suitNames[i]);
	}

	subjectNames.Empty();
	faceNames.Empty();
	suitNames.Empty();
}

bool FVirtualProductionSource::RequestSourceShutdown()
{
	ClearAllSubjects();
	instance = nullptr;
	return true;
}

void FVirtualProductionSource::HandleFaceData(FFace face) {
	//UE_LOG(LogTemp, Warning, TEXT("Creating a new face %s - %f"), *face.GetSubjectName().ToString(), face.jawOpen);
	faceNames.Add(face.GetSubjectName());
	FLiveLinkRefSkeleton skeletonRef;
	Client->PushSubjectSkeleton(SourceGuid, face.GetSubjectName(), skeletonRef);
}

void FVirtualProductionSource::HandleSubjectData(FVirtualProductionSubject virtualProductionObject)
{
	//UE_LOG(LogTemp, Warning, TEXT("SKELETON!! "), skeleton);
	subjectNames.Add(virtualProductionObject.name);
	FLiveLinkRefSkeleton skeletonRef;
	TArray<FName> boneNames;
	boneNames.Add("Root");
	skeletonRef.SetBoneNames(boneNames);
	TArray<int32> boneParents;
	boneParents.Add(0);
	skeletonRef.SetBoneParents(boneParents);
	Client->PushSubjectSkeleton(SourceGuid, virtualProductionObject.name, skeletonRef);
}
	
void FVirtualProductionSource::HandleSuitData(SuitData suit) {
	suitNames.Add(suit.GetSubjectName());
	suitNames.Add(suit.GetBindSubjectName());
	FLiveLinkRefSkeleton skeletonRef;
	TArray<FName> boneNames;
	boneNames.Add("Base");
	boneNames.Add("Hips");
	boneNames.Add("Spine");
	boneNames.Add("Spine2");
	boneNames.Add("Neck");
	boneNames.Add("Head");

	boneNames.Add("LeftShoulder");
	boneNames.Add("LeftArm");
	boneNames.Add("LeftForeArm");
	boneNames.Add("LeftHand");
	
	boneNames.Add("RightShoulder");
	boneNames.Add("RightArm");
	boneNames.Add("RightForeArm");
	boneNames.Add("RightHand");

	boneNames.Add("LeftUpLeg");
	boneNames.Add("LeftLeg");
	boneNames.Add("LeftFoot");

	boneNames.Add("RightUpLeg");
	boneNames.Add("RightLeg");
	boneNames.Add("RightFoot");


	TArray<int32> boneParents;
	boneParents.Add(0); //0 - root
	boneParents.Add(0); //1 - hip
	boneParents.Add(1); //2 - spine
	boneParents.Add(2); //3 - spine2
	boneParents.Add(3); //4 - neck
	boneParents.Add(4); //5 - head

	boneParents.Add(3); //6 - LeftShoulder
	boneParents.Add(6); //7 - LeftArm
	boneParents.Add(7); //8 - LeftForearm
	boneParents.Add(8); //9 - LeftHand

	boneParents.Add(3); //10 - RightShoulder
	boneParents.Add(10); //11 - RightArm
	boneParents.Add(11); //12 - RightForearm
	boneParents.Add(12); //13 - RightHand

	boneParents.Add(1); //14 - LeftUpLeg
	boneParents.Add(14); //15 - LeftLeg
	boneParents.Add(15); //16 - LeftFoot

	boneParents.Add(1); //17 - RightUpLeg
	boneParents.Add(17); //18 - RightLeg
	boneParents.Add(18); //19 - RightFoot

	skeletonRef.SetBoneNames(boneNames);
	skeletonRef.SetBoneParents(boneParents);
	Client->PushSubjectSkeleton(SourceGuid, suit.GetSubjectName(), skeletonRef);

	FLiveLinkRefSkeleton skeletonRef2;
	TArray<FName> boneNames2;
	boneNames2.Add("Base");
	boneNames2.Add("Hips");
	boneNames2.Add("Spine");
	boneNames2.Add("Spine2");
	boneNames2.Add("Neck");
	boneNames2.Add("Head");

	boneNames2.Add("LeftShoulder");
	boneNames2.Add("LeftArm");
	boneNames2.Add("LeftForeArm");
	boneNames2.Add("LeftHand");

	boneNames2.Add("RightShoulder");
	boneNames2.Add("RightArm");
	boneNames2.Add("RightForeArm");
	boneNames2.Add("RightHand");

	boneNames2.Add("LeftUpLeg");
	boneNames2.Add("LeftLeg");
	boneNames2.Add("LeftFoot");

	boneNames2.Add("RightUpLeg");
	boneNames2.Add("RightLeg");
	boneNames2.Add("RightFoot");


	TArray<int32> boneParents2;
	boneParents2.Add(0); //0 - root
	boneParents2.Add(0); //1 - hip
	boneParents2.Add(1); //2 - spine
	boneParents2.Add(2); //3 - spine2
	boneParents2.Add(3); //4 - neck
	boneParents2.Add(4); //5 - head

	boneParents2.Add(3); //6 - LeftShoulder
	boneParents2.Add(6); //7 - LeftArm
	boneParents2.Add(7); //8 - LeftForearm
	boneParents2.Add(8); //9 - LeftHand

	boneParents2.Add(3); //10 - RightShoulder
	boneParents2.Add(10); //11 - RightArm
	boneParents2.Add(11); //12 - RightForearm
	boneParents2.Add(12); //13 - RightHand

	boneParents2.Add(1); //14 - LeftUpLeg
	boneParents2.Add(14); //15 - LeftLeg
	boneParents2.Add(15); //16 - LeftFoot

	boneParents2.Add(1); //17 - RightUpLeg
	boneParents2.Add(17); //18 - RightLeg
	boneParents2.Add(18); //19 - RightFoot

	skeletonRef2.SetBoneNames(boneNames2);
	skeletonRef2.SetBoneParents(boneParents2);

	Client->PushSubjectSkeleton(SourceGuid, suit.GetBindSubjectName(), skeletonRef2);
}

void FVirtualProductionSource::CreateJoint(TArray<FTransform>& transforms, int32 index, Sensor* parent, Sensor* sensor) {
	
	int32 transformIndex = transforms.AddUninitialized(1);
	if (!sensor) {
		transforms[transformIndex].SetLocation(FVector(0, 0, 0));
		transforms[transformIndex].SetRotation(FQuat::Identity);
		transforms[transformIndex].SetScale3D(FVector(1, 1, 1));
	} else if (parent) {
		FQuat parentRealRotation;
		if (index == -1) {
			parentRealRotation = parent->Uquaternion() * FQuat::MakeFromEuler(FVector(0, 0, 180));
		}
		else {
			parentRealRotation = parent->Uquaternion();
		}

		//FVector realSensorPosition;
		//float chestOffset = 20;
		//if (sensor->addr == SENSOR_NECK) {
		//	realSensorPosition 
		//	
		//} else if (sensor->addr == SENSOR_LEFT_SHOULDER || sensor->addr == SENSOR_RIGHT_SHOULDER) {
		//	FVector direction = sensor->UPosition();
		//	direction.Normalize();
		//	realSensorPosition = sensor->UPosition() + (direction * (-chestOffset));
		//}
		//else {
		//	realSensorPosition = sensor->UPosition();
		//}

		
		//FVector realParentPosition;
		//if (parent->addr == SENSOR_CHEST) {

		//}
		//else {
		//	realParentPosition = parent->UPosition();
		//}
		if (sensor->addr == SENSOR_NECK) {
			transforms[transformIndex].SetLocation(FVector(0, 20.150345, 0));
		}
		else if (sensor->addr == SENSOR_RIGHT_SHOULDER) {
			transforms[transformIndex].SetLocation(FVector(7, 12.368073, 1.90378));
		}
		else if (sensor->addr == SENSOR_LEFT_SHOULDER) {
			transforms[transformIndex].SetLocation(FVector(-7, 12.368073, 1.90378));
		}
		else {
			transforms[transformIndex].SetLocation(parentRealRotation.Inverse() * (sensor->UPosition() - parent->UPosition()));
		}
		transforms[transformIndex].SetRotation(parentRealRotation.Inverse() * sensor->Uquaternion());
		transforms[transformIndex].SetScale3D(FVector(1, 1, 1));
	}
	else {
		FQuat modifier = FQuat::MakeFromEuler(FVector(0, 0, 180));
		transforms[transformIndex].SetLocation(sensor->UPosition());
		transforms[transformIndex].SetRotation(sensor->Uquaternion() * modifier);
		transforms[transformIndex].SetScale3D(FVector(1, 1, 1));
	}
}

void FVirtualProductionSource::CreateBindJoint(TArray<FTransform>& transforms, FVector position, FVector euler) {
	int32 transformIndex = transforms.AddUninitialized(1);
	transforms[transformIndex].SetLocation(position);
	transforms[transformIndex].SetRotation(FQuat::MakeFromEuler(euler));
	transforms[transformIndex].SetScale3D(FVector(1, 1, 1));
}

void FVirtualProductionSource::HandleSuits(TArray<SuitData> suits) {
	//UE_LOG(LogTemp, Warning, TEXT("Handling faces %d"), faces.Num());
	existingSuits.Empty();
	notExistingSubjects.Empty();
	for (int subjectIndex = 0; subjectIndex < suits.Num(); subjectIndex++) {
		SuitData subject = suits[subjectIndex];

		//check in the known subjects list which ones don't exist anymore in subjects, and clear the ones that don't exist
		bool nameExists = false;
		for (int suitNameIndex = 0; suitNameIndex < suitNames.Num(); suitNameIndex++) {
			if (subject.GetSubjectName() == suitNames[suitNameIndex]) {
				nameExists = true;
				existingSuits.Add(subject);
				break;
			}
		}

		if (!nameExists) {
			existingSuits.Add(subject);
			HandleSuitData(subject);
		}
		//check in the subjects for the ones that don't exist in the known subjects list and create the ones that don't exist
		if (subjectIndex == suits.Num() - 1) {
			for (int i = 0; i < suitNames.Num(); i++) {
				bool subjectExists = false;
				for (int j = 0; j < existingSuits.Num(); j++) {
					if (suitNames[i] == existingSuits[j].GetSubjectName()) {
						subjectExists = true;
					}
				}
				if (!subjectExists) {
					notExistingSubjects.Add(suitNames[i]);
				}
			}

			for (int i = 0; i < notExistingSubjects.Num(); i++) {
				//UE_LOG(LogTemp, Warning, TEXT("Removing face"));
				//Client->ClearSubject(notExistingSubjects[i]);
				//suitNames.RemoveSingle(notExistingSubjects[i]);
				//notExistingSubjects.RemoveAt(i);
			}
		}


		FLiveLinkFrameData FrameData;
		FTimer timer;
		FrameData.WorldTime = FLiveLinkWorldTime((double)(timer.GetCurrentTime()));
		TArray<FTransform>& transforms = FrameData.Transforms;
		transforms.Reset(20);
		int32 transformIndex = transforms.AddUninitialized(1);
		
		transforms[transformIndex].SetLocation(FVector(0, 0, 0));
		transforms[transformIndex].SetRotation(FQuat::Identity);
		transforms[transformIndex].SetScale3D(FVector(1, 1, 1));

		CreateJoint(transforms, 0, nullptr, subject.Hip());
		CreateJoint(transforms, -1, subject.Hip(), subject.GetSensor(SENSOR_STOMACH));
		CreateJoint(transforms, 0, subject.GetSensor(SENSOR_STOMACH), subject.GetSensor(SENSOR_CHEST));
		CreateJoint(transforms, 0, subject.GetSensor(SENSOR_CHEST), subject.GetSensor(SENSOR_NECK));
		CreateJoint(transforms, 0, subject.GetSensor(SENSOR_NECK), subject.GetSensor(SENSOR_HEAD));

		CreateJoint(transforms, 0, subject.GetSensor(SENSOR_CHEST), subject.GetSensor(SENSOR_LEFT_SHOULDER));
		CreateJoint(transforms, 0, subject.GetSensor(SENSOR_LEFT_SHOULDER), subject.GetSensor(SENSOR_LEFT_UPPER_ARM));
		CreateJoint(transforms, 0, subject.GetSensor(SENSOR_LEFT_UPPER_ARM), subject.GetSensor(SENSOR_LEFT_LOWER_ARM));
		CreateJoint(transforms, 0, subject.GetSensor(SENSOR_LEFT_LOWER_ARM), subject.GetSensor(SENSOR_LEFT_HAND));

		CreateJoint(transforms, 0, subject.GetSensor(SENSOR_CHEST), subject.GetSensor(SENSOR_RIGHT_SHOULDER));
		CreateJoint(transforms, 0, subject.GetSensor(SENSOR_RIGHT_SHOULDER), subject.GetSensor(SENSOR_RIGHT_UPPER_ARM));
		CreateJoint(transforms, 0, subject.GetSensor(SENSOR_RIGHT_UPPER_ARM), subject.GetSensor(SENSOR_RIGHT_LOWER_ARM));
		CreateJoint(transforms, 0, subject.GetSensor(SENSOR_RIGHT_LOWER_ARM), subject.GetSensor(SENSOR_RIGHT_HAND));

		CreateJoint(transforms, -1, subject.GetSensor(SENSOR_HIP), subject.GetSensor(SENSOR_LEFT_UPPER_LEG));
		CreateJoint(transforms, 0, subject.GetSensor(SENSOR_LEFT_UPPER_LEG), subject.GetSensor(SENSOR_LEFT_LOWER_LEG));
		CreateJoint(transforms, 0, subject.GetSensor(SENSOR_LEFT_LOWER_LEG), subject.GetSensor(SENSOR_LEFT_FOOT));
		
		CreateJoint(transforms, -1, subject.GetSensor(SENSOR_HIP), subject.GetSensor(SENSOR_RIGHT_UPPER_LEG));
		CreateJoint(transforms, 0, subject.GetSensor(SENSOR_RIGHT_UPPER_LEG), subject.GetSensor(SENSOR_RIGHT_LOWER_LEG));
		CreateJoint(transforms, 0, subject.GetSensor(SENSOR_RIGHT_LOWER_LEG), subject.GetSensor(SENSOR_RIGHT_FOOT));
		
		Client->PushSubjectData(SourceGuid, subject.GetSubjectName(), FrameData);

		FLiveLinkFrameData FrameDataBindPose;
		FrameDataBindPose.WorldTime = FLiveLinkWorldTime((double)(timer.GetCurrentTime()));
		TArray<FTransform>& bindTrasforms = FrameDataBindPose.Transforms;
		bindTrasforms.Reset(20);
		CreateBindJoint(bindTrasforms, FVector(0, 0, 0), FVector(90, 0, 0)); // base
		CreateBindJoint(bindTrasforms, FVector(-0.0000007, -93.9969482, 3.9482567), FVector(0, 0, 0)); // hips
		CreateBindJoint(bindTrasforms, FVector(0.0000311, -8.4838419, -3.9482708), FVector(-0.0000546, 0, -179.9999847)); // spine 1
		CreateBindJoint(bindTrasforms, FVector(0.0000331, 12.7487335, -0.0000076), FVector(0, 0, 0)); // spine 2
		CreateBindJoint(bindTrasforms, FVector(0.0000042, 20.1503448, -0.0000409), FVector(0, 0, 0)); // neck
		CreateBindJoint(bindTrasforms, FVector(0.0000115, 11.1009369, 0.0000034), FVector(0, 0, 0)); // head

		CreateBindJoint(bindTrasforms, FVector(-6.9999981, 12.3680744, 1.9037932), FVector(-0.000005, -0.000041, 90.0000076)); // left shoulder
		CreateBindJoint(bindTrasforms, FVector(0.0000031, 13.6077785, 0.0), FVector(0.0000305, 90.0, -0.0000005)); // left up arm
		CreateBindJoint(bindTrasforms, FVector(0.0000915, 27.1021519, 0.000035), FVector(-0.0000373, 0.0, -0.0000636)); // left lower arm
		CreateBindJoint(bindTrasforms, FVector(-0.0000247, 28.2999878, 0.0000167), FVector(-0.00002, 0.0, -0.0)); // left hand

		CreateBindJoint(bindTrasforms, FVector(7.0000019, 12.3680725, 1.9037799), FVector(0.0000496, 0.000041, -90.0000992)); // right shoulder
		CreateBindJoint(bindTrasforms, FVector(-0.000007, 13.6077785, 0.0000115), FVector(0.0001221, -90.0, -0.0000024)); // right up arm
		CreateBindJoint(bindTrasforms, FVector(-0.0000729, 27.1021519, 0.0000326), FVector(-0.000005, 0.0, 0.0000071)); // right lower arm
		CreateBindJoint(bindTrasforms, FVector(0.0000098, 28.2999878, 0.0000454), FVector(-0.000005, 0.0, 0.0000066)); // right hand

		CreateBindJoint(bindTrasforms, FVector(8.0999508, 0.0, 0.0), FVector(0.0, 90.0, 0.0)); // left up leg
		CreateBindJoint(bindTrasforms, FVector(-0.0000033, 43.1999855, 0.0000134), FVector(-0.000148, 0.0000205, 0.0)); // left lower leg
		CreateBindJoint(bindTrasforms, FVector(0.0000114, 43.2999763, -0.062567), FVector(90.0000916, 90.0, 0.0)); // left foot

		CreateBindJoint(bindTrasforms, FVector(-8.0999508, -0.0, -0.0000002), FVector(0.0, -90.0, 0.0)); // right up leg
		CreateBindJoint(bindTrasforms, FVector(0.0000021, 43.2000084, 0.0000048), FVector(-0.000005, -0.0000068, 0.0)); // right lower leg
		CreateBindJoint(bindTrasforms, FVector(0.000005, 43.2999878, 0.0625553), FVector(90.0, -90.0, 0.0)); // right foot

		Client->PushSubjectData(SourceGuid, subject.GetBindSubjectName(), FrameDataBindPose);
	}
}

void FVirtualProductionSource::HandleFace(TArray<FFace> faces) {
	//UE_LOG(LogTemp, Warning, TEXT("Handling faces %d"), faces.Num());
	existingFaces.Empty();
	notExistingSubjects.Empty();
	for (int subjectIndex = 0; subjectIndex < faces.Num(); subjectIndex++) {
		FFace subject = faces[subjectIndex];

		//check in the known subjects list which ones don't exist anymore in subjects, and clear the ones that don't exist
		bool nameExists = false;
		for (int faceNameIndex = 0; faceNameIndex < faceNames.Num(); faceNameIndex++) {
			if (subject.GetSubjectName() == faceNames[faceNameIndex]) {
				nameExists = true;
				existingFaces.Add(subject);
				break;
			}
		}

		if (!nameExists) {
			existingFaces.Add(subject);
			HandleFaceData(subject);
		}
		//check in the subjects for the ones that don't exist in the known subjects list and create the ones that don't exist
		if (subjectIndex == faces.Num() - 1) {
			for (int i = 0; i < faceNames.Num(); i++) {
				bool subjectExists = false;
				for (int j = 0; j < existingFaces.Num(); j++) {
					if (faceNames[i] == existingFaces[j].GetSubjectName()) {
						subjectExists = true;
					}
				}
				if (!subjectExists) {
					notExistingSubjects.Add(faceNames[i]);
				}
			}

			for (int i = 0; i < notExistingSubjects.Num(); i++) {
				//UE_LOG(LogTemp, Warning, TEXT("Removing face"));
				Client->ClearSubject(notExistingSubjects[i]);
				faceNames.RemoveSingle(notExistingSubjects[i]);
				notExistingSubjects.RemoveAt(i);
			}
		}


		FLiveLinkFrameData FrameData;
		FTimer timer;
		FrameData.WorldTime = FLiveLinkWorldTime((double)(timer.GetCurrentTime()));
		TArray<FLiveLinkCurveElement>& BlendShapes = FrameData.CurveElements;
		BlendShapes.Reset(52);
		
		int32 blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "browDownLeft";
		BlendShapes[blendIndex].CurveValue = subject.browDownLeft;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "browDownRight";
		BlendShapes[blendIndex].CurveValue = subject.browDownRight;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "browInnerUp";
		BlendShapes[blendIndex].CurveValue = subject.browInnerUp;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "browOuterUpLeft";
		BlendShapes[blendIndex].CurveValue = subject.browOuterUpLeft;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "browOuterUpRight";
		BlendShapes[blendIndex].CurveValue = subject.browOuterUpRight;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "cheekPuff";
		BlendShapes[blendIndex].CurveValue = subject.cheekPuff;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "cheekSquintLeft";
		BlendShapes[blendIndex].CurveValue = subject.cheekSquintLeft;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "cheekSquintRight";
		BlendShapes[blendIndex].CurveValue = subject.cheekSquintRight;
		
		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "eyeBlinkLeft";
		BlendShapes[blendIndex].CurveValue = subject.eyeBlinkLeft;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "eyeBlinkRight";
		BlendShapes[blendIndex].CurveValue = subject.eyeBlinkRight;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "eyeLookDownLeft";
		BlendShapes[blendIndex].CurveValue = subject.eyeLookDownLeft;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "eyeLookDownRight";
		BlendShapes[blendIndex].CurveValue = subject.eyeLookDownRight;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "eyeLookInLeft";
		BlendShapes[blendIndex].CurveValue = subject.eyeLookInLeft;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "eyeLookInRight";
		BlendShapes[blendIndex].CurveValue = subject.eyeLookInRight;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "eyeLookOutLeft";
		BlendShapes[blendIndex].CurveValue = subject.eyeLookOutLeft;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "eyeLookOutRight";
		BlendShapes[blendIndex].CurveValue = subject.eyeLookOutRight;


		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "eyeLookUpLeft";
		BlendShapes[blendIndex].CurveValue = subject.eyeLookUpLeft;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "eyeLookUpRight";
		BlendShapes[blendIndex].CurveValue = subject.eyeLookUpRight;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "eyeSquintLeft";
		BlendShapes[blendIndex].CurveValue = subject.eyeSquintLeft;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "eyeSquintRight";
		BlendShapes[blendIndex].CurveValue = subject.eyeSquintRight;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "eyeWideLeft";
		BlendShapes[blendIndex].CurveValue = subject.eyeWideLeft;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "eyeWideRight";
		BlendShapes[blendIndex].CurveValue = subject.eyeWideRight;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "jawOpen";
		BlendShapes[blendIndex].CurveValue = subject.jawOpen;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "jawForward";
		BlendShapes[blendIndex].CurveValue = subject.jawForward;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "jawLeft";
		BlendShapes[blendIndex].CurveValue = subject.jawLeft;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "jawRight";
		BlendShapes[blendIndex].CurveValue = subject.jawRight;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "mouthClose";
		BlendShapes[blendIndex].CurveValue = subject.mouthClose;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "mouthDimpleLeft";
		BlendShapes[blendIndex].CurveValue = subject.mouthDimpleLeft;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "mouthDimpleRight";
		BlendShapes[blendIndex].CurveValue = subject.mouthDimpleRight;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "mouthFrownLeft";
		BlendShapes[blendIndex].CurveValue = subject.mouthFrownLeft;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "mouthFrownRight";
		BlendShapes[blendIndex].CurveValue = subject.mouthFrownRight;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "mouthFunnel";
		BlendShapes[blendIndex].CurveValue = subject.mouthFunnel;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "mouthLeft";
		BlendShapes[blendIndex].CurveValue = subject.mouthLeft;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "mouthLowerDownLeft";
		BlendShapes[blendIndex].CurveValue = subject.mouthLowerDownLeft;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "mouthLowerDownRight";
		BlendShapes[blendIndex].CurveValue = subject.mouthLowerDownRight;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "mouthPressLeft";
		BlendShapes[blendIndex].CurveValue = subject.mouthPressLeft;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "mouthPressRight";
		BlendShapes[blendIndex].CurveValue = subject.mouthPressRight;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "mouthPucker";
		BlendShapes[blendIndex].CurveValue = subject.mouthPucker;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "mouthRight";
		BlendShapes[blendIndex].CurveValue = subject.mouthRight;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "mouthRollLower";
		BlendShapes[blendIndex].CurveValue = subject.mouthRollLower;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "mouthRollUpper";
		BlendShapes[blendIndex].CurveValue = subject.mouthRollUpper;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "mouthShrugLower";
		BlendShapes[blendIndex].CurveValue = subject.mouthShrugLower;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "mouthShrugUpper";
		BlendShapes[blendIndex].CurveValue = subject.mouthShrugUpper;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "mouthSmileLeft";
		BlendShapes[blendIndex].CurveValue = subject.mouthSmileLeft;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "mouthSmileRight";
		BlendShapes[blendIndex].CurveValue = subject.mouthSmileRight;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "mouthStretchLeft";
		BlendShapes[blendIndex].CurveValue = subject.mouthStretchLeft;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "mouthStretchRight";
		BlendShapes[blendIndex].CurveValue = subject.mouthStretchRight;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "mouthUpperUpLeft";
		BlendShapes[blendIndex].CurveValue = subject.mouthUpperUpLeft;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "mouthUpperUpRight";
		BlendShapes[blendIndex].CurveValue = subject.mouthUpperUpRight;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "noseSneerLeft";
		BlendShapes[blendIndex].CurveValue = subject.noseSneerLeft;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "noseSneerRight";
		BlendShapes[blendIndex].CurveValue = faces[subjectIndex].noseSneerRight;

		blendIndex = BlendShapes.AddUninitialized(1);
		BlendShapes[blendIndex].CurveName = "tongueOut";
		BlendShapes[blendIndex].CurveValue = faces[subjectIndex].tongueOut;

		Client->PushSubjectData(SourceGuid, subject.GetSubjectName(), FrameData);
	}
}


void FVirtualProductionSource::HandleSubjectFrame(TArray<FVirtualProductionSubject> subjects)
{
	existingSubjects.Empty();
	notExistingSubjects.Empty();

	for (int i = 0; i < subjectNames.Num(); i++) {
		bool subjectExists = false;
		for (int j = 0; j < subjects.Num(); j++) {
			if (subjectNames[i] == subjects[j].name) {
				subjectExists = true;
			}
		}
		if (!subjectExists) {
			notExistingSubjects.Add(subjectNames[i]);
		}
	}

	for (int i = 0; i < notExistingSubjects.Num(); i++) {
		Client->ClearSubject(notExistingSubjects[i]);
		subjectNames.RemoveSingle(notExistingSubjects[i]);
	}

	for (int subjectIndex = 0; subjectIndex < subjects.Num(); subjectIndex++) {
		FVirtualProductionSubject subject = subjects[subjectIndex];
		
		//check in the known subjects list which ones don't exist anymore in subjects, and clear the ones that don't exist
		bool nameExists = false;
		for (int subjectNameIndex = 0; subjectNameIndex < subjectNames.Num(); subjectNameIndex++) {
			if (subject.name == subjectNames[subjectNameIndex]) {
				nameExists = true;
				existingSubjects.Add(subject);
				break;
			}
		}

		if (!nameExists) {
			existingSubjects.Add(subject);
			HandleSubjectData(subject);
			existingSubjects.Add(subject);
		}

		FTransform hardCodedTransform;
		hardCodedTransform.SetTranslation(subject.position);
		hardCodedTransform.SetRotation(subject.rotation);
		hardCodedTransform.SetScale3D(FVector(1, 1, 1));

		FLiveLinkFrameData FrameData;
		FrameData.Transforms.Add(hardCodedTransform);
		FTimer timer;

		FrameData.WorldTime = FLiveLinkWorldTime((double)(timer.GetCurrentTime()));

		Client->PushSubjectData(SourceGuid, subject.name, FrameData);

	}
}