#pragma once

#include "PhysicsEngine.h"
#include <iostream>
#include <iomanip>

namespace PhysicsEngine
{
	///Plane class
	class Plane : public StaticActor
	{
	public:
		//A plane with default paramters: XZ plane centred at (0,0,0)
		Plane(PxVec3 normal = PxVec3(0.f, 1.f, 0.f), PxReal distance = 0.f)
			: StaticActor(PxTransformFromPlaneEquation(PxPlane(normal, distance)))
		{
			CreateShape(PxPlaneGeometry());
		}
	};

	//Box class
	class Box : public StaticActor
	{
	public:
		Box(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(1.f, 1.f, 1.f), PxReal density = 1.f)
			: StaticActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
		}
	};

	class TrampTop : public DynamicActor
	{
	public:
		TrampTop(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(1.f, 1.f, 1.f), PxReal density = 1.f)
			: DynamicActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
			GetShape(0)->setLocalPose(PxTransform(PxVec3(18.5f, 1.f, 49.f), PxQuat(PxPi / 2, PxVec3(1.f, 0.f, .0f))));
		}
	};

	//****************************************************************PinBall*******************************************************
	//Sphere class
	class Sphere : public DynamicActor
	{
	public:
		Sphere(const PxTransform& pose = PxTransform(PxIdentity), PxReal radius = 1.f, PxReal density = 1.f)
			: DynamicActor(pose)
		{
			CreateShape(PxSphereGeometry(radius), density);
			GetShape(0)->setLocalPose(PxTransform(PxVec3(0.f, .0f, 0.f)));
		}
	};
	//******************************************************************************************************************************

	//****************************************************************Barriers******************************************************

	//Arena walls
	class Walls : public StaticActor
	{
	public:
		Walls(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.5f, 3.f, 50.f), PxReal density = 1.f)
			: StaticActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(.5f, 1.f, 48.f), density);
			CreateShape(PxBoxGeometry(1.f, 3.f, .5f), density);
			CreateShape(PxBoxGeometry(.5f, 3.f, 10.f), density);
			CreateShape(PxBoxGeometry(.5f, 3.f, 10.f), density);
			//Right wall
			GetShape(0)->setLocalPose(PxTransform(PxVec3(25.f, 0.f, 0.f)));
			//Left wall
			GetShape(1)->setLocalPose(PxTransform(PxVec3(-25.f, .0f, 0.f)));
			//Interior wall forming shoot
			GetShape(2)->setLocalPose(PxTransform(PxVec3(22.f, -2.0f, 2.f)));
			//Cap on bottom of pinball shoot
			GetShape(3)->setLocalPose(PxTransform(PxVec3(23.5f, .0f, 49.5f)));
			//Right slope
			GetShape(4)->setLocalPose(PxTransform(PxVec3(14.f, .0f, 40.0f), PxQuat(5.4105206812, PxVec3(.0f, 1.f, .0f))));
			//Left Slope
			GetShape(5)->setLocalPose(PxTransform(PxVec3(-17.5f, .0f, 40.0f), PxQuat(-5.4105206812, PxVec3(.0f, 1.f, .0f))));
		}

	};

	//Curved Wall
	class Wall2 : public StaticActor
	{
	public:
		Wall2(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(6.f, 3.f, .5f), PxReal density = 1.f)
			: StaticActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			//Middle Block
			GetShape(0)->setLocalPose(PxTransform(PxVec3(0.f, .0f, 0.f)));
			//Left Hand blocks
			GetShape(1)->setLocalPose(PxTransform(PxVec3(-11.f, 0.f, 2.25f), PxQuat(0.3926991f, PxVec3(.0f, 1.f, .0f))));
			GetShape(2)->setLocalPose(PxTransform(PxVec3(-20.75f, 0.f, 8.75f), PxQuat(0.7853982f, PxVec3(.0f, 1.f, .0f))));
			//Right Hand blocks
			GetShape(3)->setLocalPose(PxTransform(PxVec3(11.f, 0.f, 2.25f), PxQuat(5.8904862f, PxVec3(.0f, 1.f, .0f))));
			GetShape(4)->setLocalPose(PxTransform(PxVec3(20.75f, 0.f, 8.75f), PxQuat(5.49779f, PxVec3(.0f, 1.f, .0f))));

		}

	};

	//Small Curved Wall
	class sCWall : public StaticActor
	{
	public:
		sCWall(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(2.f, 3.f, .5f), PxReal density = 1.f)
			: StaticActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			//Middle Block
			GetShape(0)->setLocalPose(PxTransform(PxVec3(0.f, .0f, 0.f)));
			//Top two blocks
			GetShape(1)->setLocalPose(PxTransform(PxVec3(-3.75f, 0.f, .75f), PxQuat(0.3926991f, PxVec3(.0f, 1.f, .0f))));
			GetShape(2)->setLocalPose(PxTransform(PxVec3(-6.75f, 0.f, 2.75f), PxQuat(0.7853982f, PxVec3(.0f, 1.f, .0f))));
			//Bottom two blocks
			GetShape(3)->setLocalPose(PxTransform(PxVec3(3.75f, 0.f, .75f), PxQuat(5.8904862f, PxVec3(.0f, 1.f, .0f))));
			GetShape(4)->setLocalPose(PxTransform(PxVec3(6.75f, 0.f, 2.75f), PxQuat(5.49779f, PxVec3(.0f, 1.f, .0f))));

		}

	};

	//Left group of curved walls
	class sCWall2 : public StaticActor
	{
	public:
		sCWall2(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(2.f, 3.f, .5f), PxReal density = 1.f)
			: StaticActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			//Lower Curve*******************
			//Middle block
			GetShape(0)->setLocalPose(PxTransform(PxVec3(0.f, .0f, 0.f)));
			//Top two blocks
			GetShape(1)->setLocalPose(PxTransform(PxVec3(-3.75f, 0.f, .75f), PxQuat(0.3926991f, PxVec3(.0f, 1.f, .0f))));
			GetShape(2)->setLocalPose(PxTransform(PxVec3(-6.75f, 0.f, 2.75f), PxQuat(0.7853982f, PxVec3(.0f, 1.f, .0f))));
			//Lower two blocks
			GetShape(3)->setLocalPose(PxTransform(PxVec3(3.75f, 0.f, .75f), PxQuat(5.8904862f, PxVec3(.0f, 1.f, .0f))));
			GetShape(4)->setLocalPose(PxTransform(PxVec3(6.75f, 0.f, 2.75f), PxQuat(5.49779f, PxVec3(.0f, 1.f, .0f))));
			//Mid Curve*********************
			//Middle block
			GetShape(5)->setLocalPose(PxTransform(PxVec3(-15.75f, .0f, 8.f)));
			//Lower two blocks
			GetShape(6)->setLocalPose(PxTransform(PxVec3(-12.25f, 0.f, 7.25f), PxQuat(0.3926991f, PxVec3(.0f, 1.f, .0f))));
			GetShape(7)->setLocalPose(PxTransform(PxVec3(-9.25f, 0.f, 5.25f), PxQuat(0.7853982f, PxVec3(.0f, 1.f, .0f))));
			//Top two blocks
			GetShape(8)->setLocalPose(PxTransform(PxVec3(-19.5f, 0.f, 7.25f), PxQuat(5.8904862f, PxVec3(.0f, 1.f, .0f))));
			GetShape(9)->setLocalPose(PxTransform(PxVec3(-22.5f, 0.f, 5.25f), PxQuat(5.49779f, PxVec3(.0f, 1.f, .0f))));
			//Upper Curve
			//Middle block
			GetShape(10)->setLocalPose(PxTransform(PxVec3(-39.f, 0.f, 10.f), PxQuat(PxPi / 2, PxVec3(.0f, 1.f, .0f))));
			//Left two blocks
			GetShape(11)->setLocalPose(PxTransform(PxVec3(-38.f, 0.f, 13.5f), PxQuat(2 * PxPi / 3, PxVec3(.0f, 1.f, .0f))));
			GetShape(12)->setLocalPose(PxTransform(PxVec3(-35.5f, 0.f, 16.f), PxQuat(5 * PxPi / 6, PxVec3(.0f, 1.f, .0f))));
			//Right two blocks
			GetShape(13)->setLocalPose(PxTransform(PxVec3(-38.f, 0.f, 6.5f), PxQuat(-2 * PxPi / 3, PxVec3(.0f, 1.f, .0f))));
			GetShape(14)->setLocalPose(PxTransform(PxVec3(-35.5f, 0.f, 4.f), PxQuat(-5 * PxPi / 6, PxVec3(.0f, 1.f, .0f))));
		}

	};

	//*****************************************************************************************************************************

	//***************************************************StationaryObjects*********************************************************
	//Triangle
	class Triangle : public StaticActor
	{
	public:
		Triangle(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.1f, 3.f, 7.f), PxReal density = 1.f)
			: StaticActor(pose)
		{
			CreateShape(PxBoxGeometry(.1f, 3.f, 7.f), density);
			CreateShape(PxBoxGeometry(.1f, 3.f, 4.1f), density);
			CreateShape(PxBoxGeometry(.1f, 3.f, 4.1f), density);
			//Bottom piece of triangle
			GetShape(0)->setLocalPose(PxTransform(PxVec3(0.f, 0.f, 2.f), PxQuat(PxPi / 2, PxVec3(.0f, 1.f, .0f))));
			//Right slope
			GetShape(1)->setLocalPose(PxTransform(PxVec3(3.5f, 0.f, 0.f), PxQuat(PxPi / 3, PxVec3(.0f, 1.f, .0f))));
			//Left slope
			GetShape(2)->setLocalPose(PxTransform(PxVec3(-3.5f, 0.f, 0.f), PxQuat(-PxPi / 3, PxVec3(.0f, 1.f, .0f))));
		}

	};


	//Pins to prevent Paddles from dropping too far
	class Pin : public StaticActor
	{
	public:
		Pin(const PxTransform& pose = PxTransform(PxIdentity), PxVec2 dimensions = PxVec2(.5f, .5f), PxReal density = 1.f)
			: StaticActor(pose)
		{
			CreateShape(PxCapsuleGeometry(dimensions.x, dimensions.y), density);
			CreateShape(PxCapsuleGeometry(dimensions.x, dimensions.y), density);
			//Left Pin
			GetShape(0)->setLocalPose(PxTransform(PxVec3(-7.f, .0f, .0f), PxQuat(PxPi / 2, PxVec3(.0f, 0.f, 1.f))));
			//Right Pin
			GetShape(1)->setLocalPose(PxTransform(PxVec3(3.7f, .0f, .0f), PxQuat(PxPi / 2, PxVec3(.0f, 0.f, 1.f))));
		}
	};

	
	//Bouncer Group1 (top 5 bouncers)
	class BouncerG1 : public StaticActor
	{
	public:
		BouncerG1(const PxTransform& pose = PxTransform(PxIdentity), PxVec2 dimensions = PxVec2(1.5f, 1.5f), PxReal density = 1.f)
			: StaticActor(pose)
		{
			CreateShape(PxCapsuleGeometry(dimensions.x, dimensions.y), density);
			CreateShape(PxCapsuleGeometry(dimensions.x, dimensions.y), density);
			CreateShape(PxCapsuleGeometry(dimensions.x, dimensions.y), density);
			CreateShape(PxCapsuleGeometry(dimensions.x, dimensions.y), density);
			CreateShape(PxCapsuleGeometry(dimensions.x, dimensions.y), density);
			//Upper Right Bouncer
			GetShape(0)->setLocalPose(PxTransform(PxVec3(0.f, 0.f, 0.f)));
			//Lower right bouncer
			GetShape(1)->setLocalPose(PxTransform(PxVec3(0.f, 5.f, 10.f)));
			//Upper Left bouncer
			GetShape(2)->setLocalPose(PxTransform(PxVec3(0.f, 10.f, -5.f)));
			//Lower left bouncer
			GetShape(3)->setLocalPose(PxTransform(PxVec3(0.f, 15.f, 5.f)));
			//Bouncer in top left corner of arena
			GetShape(4)->setLocalPose(PxTransform(PxVec3(0.f, 25.f, -10.f)));
		}
	};

	//Bouncer Group2 (Bouncers down left shoot and below right hand curve)
	class BouncerG2 : public StaticActor
	{
	public:
		BouncerG2(const PxTransform& pose = PxTransform(PxIdentity), PxVec2 dimensions = PxVec2(1.5f, 1.5f), PxReal density = 1.f)
			: StaticActor(pose)
		{
			CreateShape(PxCapsuleGeometry(dimensions.x, dimensions.y), density);
			CreateShape(PxCapsuleGeometry(dimensions.x, dimensions.y), density);
			CreateShape(PxCapsuleGeometry(dimensions.x, dimensions.y), density);
			CreateShape(PxCapsuleGeometry(dimensions.x, dimensions.y), density);
			CreateShape(PxCapsuleGeometry(dimensions.x, dimensions.y), density);
			//Top right of small trio
			GetShape(0)->setLocalPose(PxTransform(PxVec3(0.f, 0.f, 0.f)));
			//Top left of small trio
			GetShape(1)->setLocalPose(PxTransform(PxVec3(0.f, 9.f, 0.f)));
			//Bottom of trio
			GetShape(2)->setLocalPose(PxTransform(PxVec3(0.f, 4.5f, 7.f)));
			//Middle of board, left hand side, within the shoot
			GetShape(3)->setLocalPose(PxTransform(PxVec3(0.f, 2.f, -29.f)));
			//Middle of board, right hand side, below curved wall
			GetShape(4)->setLocalPose(PxTransform(PxVec3(0.f, -32.5f, -20.f)));

		}
	};
	//***************************************************************************************************************************

	//******************************************************MovingObjects********************************************************
	//Paddle 
	class Paddle : public DynamicActor
	{
	public:
		Paddle(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(3.f, .5f, .5f), PxReal density = 1.f)
			: DynamicActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
		}
	};

	//Motor arms
	class mArms : public DynamicActor
	{
	public:
		mArms(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.2f, 1.f, 1.5f), PxReal density = 1.f)
			: DynamicActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			GetShape(0)->setLocalPose(PxTransform(PxVec3(0.f, 2.5f, -1.5f)));
			GetShape(1)->setLocalPose(PxTransform(PxVec3(0.f, 2.5f, 1.5f)));
			GetShape(2)->setLocalPose(PxTransform(PxVec3(-1.5f, 2.5f, 0.f), PxQuat(PxPi / 2, PxVec3(.0f, 1.f, .0f))));
			GetShape(3)->setLocalPose(PxTransform(PxVec3(1.5f, 2.5f, 0.f), PxQuat(PxPi / 2, PxVec3(.0f, 1.f, .0f))));
		}
	};
	//****************************************************************************************************************************

	//****************************************************************Triggers****************************************************
	//DeathTrigger
	class DeathTrigger : public StaticActor
	{
	public:
		DeathTrigger(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(23.f, 1.f, .01f), PxReal density = 1.f)
			: StaticActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
		}

	};
	//ScoreTrigger
	class ScoreTrigger : public StaticActor
	{
	public:
		ScoreTrigger(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(1.f, 1.f, 1.f), PxReal density = 1.f)
			: StaticActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
		}

	};
	//****************************************************************************************************************************

	///The ConvexMesh class
	class ConvexMesh : public DynamicActor
	{
	public:
		//constructor
		ConvexMesh(const std::vector<PxVec3>& verts, const PxTransform& pose = PxTransform(PxIdentity), PxReal density = 1.f)
			: DynamicActor(pose)
		{
			PxConvexMeshDesc mesh_desc;
			mesh_desc.points.count = (PxU32)verts.size();
			mesh_desc.points.stride = sizeof(PxVec3);
			mesh_desc.points.data = &verts.front();
			mesh_desc.flags = PxConvexFlag::eCOMPUTE_CONVEX;
			mesh_desc.vertexLimit = 256;

			CreateShape(PxConvexMeshGeometry(CookMesh(mesh_desc)), density);
		}

		//mesh cooking (preparation)
		PxConvexMesh* CookMesh(const PxConvexMeshDesc& mesh_desc)
		{
			PxDefaultMemoryOutputStream stream;

			if (!GetCooking()->cookConvexMesh(mesh_desc, stream))
				throw new Exception("ConvexMesh::CookMesh, cooking failed.");

			PxDefaultMemoryInputData input(stream.getData(), stream.getSize());

			return GetPhysics()->createConvexMesh(input);
		}
	};

	///The TriangleMesh class
	class TriangleMesh : public StaticActor
	{
	public:
		//constructor
		TriangleMesh(const std::vector<PxVec3>& verts, const std::vector<PxU32>& trigs, const PxTransform& pose = PxTransform(PxIdentity))
			: StaticActor(pose)
		{
			PxTriangleMeshDesc mesh_desc;
			mesh_desc.points.count = (PxU32)verts.size();
			mesh_desc.points.stride = sizeof(PxVec3);
			mesh_desc.points.data = &verts.front();
			mesh_desc.triangles.count = (PxU32)trigs.size();
			mesh_desc.triangles.stride = 3 * sizeof(PxU32);
			mesh_desc.triangles.data = &trigs.front();

			CreateShape(PxTriangleMeshGeometry(CookMesh(mesh_desc)));
		}

		//mesh cooking (preparation)
		PxTriangleMesh* CookMesh(const PxTriangleMeshDesc& mesh_desc)
		{
			PxDefaultMemoryOutputStream stream;

			if (!GetCooking()->cookTriangleMesh(mesh_desc, stream))
				throw new Exception("TriangleMesh::CookMesh, cooking failed.");

			PxDefaultMemoryInputData input(stream.getData(), stream.getSize());

			return GetPhysics()->createTriangleMesh(input);
		}
	};

	//Distance joint with the springs switched on
	class DistanceJoint : public Joint
	{
	public:
		DistanceJoint(Actor* actor0, const PxTransform& localFrame0, Actor* actor1, const PxTransform& localFrame1)
		{
			PxRigidActor* px_actor0 = 0;
			if (actor0)
				px_actor0 = (PxRigidActor*)actor0->Get();

			joint = (PxJoint*)PxDistanceJointCreate(*GetPhysics(), px_actor0, localFrame0, (PxRigidActor*)actor1->Get(), localFrame1);
			joint->setConstraintFlag(PxConstraintFlag::eVISUALIZATION, true);
			((PxDistanceJoint*)joint)->setDistanceJointFlag(PxDistanceJointFlag::eSPRING_ENABLED, true);
			Damping(1.f);
			Stiffness(1.f);
		}

		void Stiffness(PxReal value)
		{
			((PxDistanceJoint*)joint)->setStiffness(value);
		}

		PxReal Stiffness()
		{
			return ((PxDistanceJoint*)joint)->getStiffness();
		}

		void Damping(PxReal value)
		{
			((PxDistanceJoint*)joint)->setDamping(value);
		}

		PxReal Damping()
		{
			return ((PxDistanceJoint*)joint)->getDamping();
		}
	};

	///Revolute Joint
	class RevoluteJoint : public Joint
	{
	public:
		RevoluteJoint(Actor* actor0, const PxTransform& localFrame0, Actor* actor1, const PxTransform& localFrame1)
		{
			PxRigidActor* px_actor0 = 0;
			if (actor0)
				px_actor0 = (PxRigidActor*)actor0->Get();

			joint = PxRevoluteJointCreate(*GetPhysics(), px_actor0, localFrame0, (PxRigidActor*)actor1->Get(), localFrame1);
			joint->setConstraintFlag(PxConstraintFlag::eVISUALIZATION, true);
		}

		void DriveVelocity(PxReal value)
		{
			//wake up the attached actors
			PxRigidDynamic *actor_0, *actor_1;
			((PxRevoluteJoint*)joint)->getActors((PxRigidActor*&)actor_0, (PxRigidActor*&)actor_1);
			if (actor_0)
			{
				if (actor_0->isSleeping())
					actor_0->wakeUp();
			}
			if (actor_1)
			{
				if (actor_1->isSleeping())
					actor_1->wakeUp();
			}
			((PxRevoluteJoint*)joint)->setDriveVelocity(value);
			((PxRevoluteJoint*)joint)->setRevoluteJointFlag(PxRevoluteJointFlag::eDRIVE_ENABLED, true);
		}

		PxReal DriveVelocity()
		{
			return ((PxRevoluteJoint*)joint)->getDriveVelocity();
		}

		void SetLimits(PxReal lower, PxReal upper)
		{
			((PxRevoluteJoint*)joint)->setLimit(PxJointAngularLimitPair(lower, upper));
			((PxRevoluteJoint*)joint)->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED, true);
		}
	};
}