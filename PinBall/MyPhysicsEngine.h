#pragma once

#include "BasicActors.h"
#include <iostream>
#include <iomanip>

namespace PhysicsEngine
{
	using namespace std;

	//a list of colours: Circus Palette
	static const PxVec3 color_palette[] = {PxVec3(46.f/255.f,9.f/255.f,39.f/255.f),PxVec3(217.f/255.f,0.f/255.f,0.f/255.f),
		PxVec3(255.f/255.f,45.f/255.f,0.f/255.f),PxVec3(255.f/255.f,140.f/255.f,54.f/255.f),PxVec3(4.f/255.f,117.f/255.f,111.f/255.f)};

	//pyramid vertices
	static PxVec3 pyramid_verts[] = {PxVec3(0,1,0), PxVec3(1,0,0), PxVec3(-1,0,0), PxVec3(0,0,1), PxVec3(0,0,-1)};
	//pyramid triangles: a list of three vertices for each triangle e.g. the first triangle consists of vertices 1, 4 and 0
	//vertices have to be specified in a counter-clockwise order to assure the correct shading in rendering
	static PxU32 pyramid_trigs[] = {1, 4, 0, 3, 1, 0, 2, 3, 0, 4, 2, 0, 3, 2, 1, 2, 4, 1};

	class Pyramid : public ConvexMesh
	{
	public:
		Pyramid(PxTransform pose=PxTransform(PxIdentity), PxReal density=1.f) :
			ConvexMesh(vector<PxVec3>(begin(pyramid_verts),end(pyramid_verts)), pose, density)
		{
		}
	};

	class PyramidStatic : public TriangleMesh
	{
	public:
		PyramidStatic(PxTransform pose=PxTransform(PxIdentity)) :
			TriangleMesh(vector<PxVec3>(begin(pyramid_verts),end(pyramid_verts)), vector<PxU32>(begin(pyramid_trigs),end(pyramid_trigs)), pose)
		{
		}
	};

	struct FilterGroup
	{
		enum Enum
		{
			DEATH		= (1 << 0),
			PINBALL		= (1 << 1),
			SCORE1		= (1 << 2),
			SCORE2		= (1 << 3),
			SCORE3		= (1 << 4),
			SCORE4		= (1 << 5),
			LAUNCH		= (1 << 6)
			//add more if you need
		};
	};

	///An example class showing the use of springs (distance joints).
	class Trampoline
	{
		vector<DistanceJoint*> springs;
		Box *bottom, *top;

	public:
		Trampoline(const PxVec3& dimensions=PxVec3(1.f,1.f,1.f), PxReal stiffness=1.f, PxReal damping=1.f)
		{
			PxReal thickness = .1f;
			bottom = new Box(PxTransform(PxVec3(0.f,thickness,0.f)),PxVec3(dimensions.x,thickness,dimensions.z));
			top = new Box(PxTransform(PxVec3(0.f,dimensions.y+thickness,0.f)),PxVec3(dimensions.x,thickness,dimensions.z));
			springs.resize(4);
			springs[0] = new DistanceJoint(bottom, PxTransform(PxVec3(dimensions.x,thickness,dimensions.z)), top, PxTransform(PxVec3(dimensions.x,-dimensions.y,dimensions.z)));
			springs[1] = new DistanceJoint(bottom, PxTransform(PxVec3(dimensions.x,thickness,-dimensions.z)), top, PxTransform(PxVec3(dimensions.x,-dimensions.y,-dimensions.z)));
			springs[2] = new DistanceJoint(bottom, PxTransform(PxVec3(-dimensions.x,thickness,dimensions.z)), top, PxTransform(PxVec3(-dimensions.x,-dimensions.y,dimensions.z)));
			springs[3] = new DistanceJoint(bottom, PxTransform(PxVec3(-dimensions.x,thickness,-dimensions.z)), top, PxTransform(PxVec3(-dimensions.x,-dimensions.y,-dimensions.z)));

			for (unsigned int i = 0; i < springs.size(); i++)
			{
				springs[i]->Stiffness(stiffness);
				springs[i]->Damping(damping);
			}
		}

		void AddToScene(Scene* scene)
		{
			scene->Add(bottom);
			scene->Add(top);
		}

		~Trampoline()
		{
			for (unsigned int i = 0; i < springs.size(); i++)
				delete springs[i];
		}
	};

	///A customised collision class, implemneting various callbacks
	class MySimulationEventCallback : public PxSimulationEventCallback
	{
	public:
		//an example variable that will be checked in the main simulation loop
		bool trigger, launchTrigger = false, deathTrigger = false, scoreTrigger10 = false, scoreTrigger50 = false , scoreTrigger100 = false;
		int score = 0, lives = 3;

		MySimulationEventCallback() : trigger(false) {}

		///Method called when the contact with the trigger object is detected.
		virtual void onTrigger(PxTriggerPair* pairs, PxU32 count) 
		{
			//Naming triggers
			string dTrigger = "Death", lTrigger = "Launcher", sTrigger10 = "Score10", sTrigger50 = "Score50", sTrigger100 = "Score100";
			//you can read the trigger information here
			for (PxU32 i = 0; i < count; i++)
			{
				//filter out contact with the planes
				if (pairs[i].otherShape->getGeometryType() != PxGeometryType::ePLANE)
				{
					//check if eNOTIFY_TOUCH_FOUND trigger
					if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_FOUND)
					{
						if (pairs[i].otherShape->getGeometryType() == PxGeometryType::eSPHERE)
						{
								if (pairs[i].triggerActor->getName() == dTrigger)
								{
									cout << "Death Triggered" << endl;
									deathTrigger = true;
									lives--;
								}
								//Trigger for launchpad
								if (pairs[i].triggerActor->getName() != lTrigger)
								{
									cout << "Launch Ready" << endl;
									launchTrigger = true;
								}
								//Triggers for scores**********
								if (pairs[i].triggerActor->getName() == sTrigger10)
								{
									score = score + 10;
									cout << "+10" << endl;
									scoreTrigger10 = true;
								}
								if (pairs[i].triggerActor->getName() == sTrigger50)
								{
									score = score + 50;
									cout << "+50" << endl;
									scoreTrigger50 = true;
								}
								if (pairs[i].triggerActor->getName() == sTrigger100)
								{
									score = score + 100;
									cout << "+100" << endl;
									scoreTrigger100 = true;
								}
								//******************************
						}
						
						//cerr << "onTrigger::eNOTIFY_TOUCH_FOUND" << endl;
						//trigger = true;
					}
					//check if eNOTIFY_TOUCH_LOST trigger
					if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_LOST)
					{
						cerr << "onTrigger::eNOTIFY_TOUCH_LOST" << endl;
						deathTrigger = false;
						launchTrigger = false;
						scoreTrigger10 = false;
						scoreTrigger50 = false;
						scoreTrigger100 = false;
					}
				}
			}
		}

		///Method called when the contact by the filter shader is detected.
		virtual void onContact(const PxContactPairHeader &pairHeader, const PxContactPair *pairs, PxU32 nbPairs) 
		{
			cerr << "Contact found between " << pairHeader.actors[0]->getName() << " " << pairHeader.actors[1]->getName() << endl;

			//check all pairs
			for (PxU32 i = 0; i < nbPairs; i++)
			{
				//check eNOTIFY_TOUCH_FOUND
				if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
				{
					cerr << "onContact::eNOTIFY_TOUCH_FOUND" << endl;
				}
				//check eNOTIFY_TOUCH_LOST
				if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_LOST)
				{
					cerr << "onContact::eNOTIFY_TOUCH_LOST" << endl;
				}
			}
		}

		virtual void onConstraintBreak(PxConstraintInfo *constraints, PxU32 count) {}
		virtual void onWake(PxActor **actors, PxU32 count) {}
		virtual void onSleep(PxActor **actors, PxU32 count) {}
	};

	//A simple filter shader based on PxDefaultSimulationFilterShader - without group filtering
	static PxFilterFlags CustomFilterShader( PxFilterObjectAttributes attributes0,	PxFilterData filterData0,
		PxFilterObjectAttributes attributes1,	PxFilterData filterData1,
		PxPairFlags& pairFlags,	const void* constantBlock,	PxU32 constantBlockSize)
	{
		// let triggers through
		if(PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
		{
			pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
			return PxFilterFlags();
		}

		pairFlags = PxPairFlag::eCONTACT_DEFAULT;
		//enable continous collision detection
//		pairFlags |= PxPairFlag::eCCD_LINEAR;
		
		
		//customise collision filtering here
		//e.g.

		// trigger the contact callback for pairs (A,B) where 
		// the filtermask of A contains the ID of B and vice versa.
		if((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
		{
			//trigger onContact callback for this pair of objects
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_LOST;
//			pairFlags |= PxPairFlag::eNOTIFY_CONTACT_POINTS;
		}

		return PxFilterFlags();
	};

	///Custom scene class
	class MyScene : public Scene
	{
		Plane* plane;
		Walls* sWall;
		Wall2* cWall;
		sCWall* sCWall1;
		sCWall2* gCWall1;
		Sphere* ball;
		PxMaterial* bouncy,* notBouncy,* veryBouncy,* zeroBounce;
		MySimulationEventCallback* my_callback;
		Trampoline* trampoline;
		BouncerG1* bouncer1;
		BouncerG2* bouncer2;
		Triangle* triangle,* triangle1,* triangle2,* triangle3,* triangle4;
		mArms* arms;
		Paddle* paddle1,* paddle2;
		Pin* pins;
		DeathTrigger* dTrigger;
		ScoreTrigger* sTrigger1,* sTrigger2,* sTrigger3,* sTrigger4,* sTrigger5, *sTrigger6, *sTrigger7,*sTrigger8, *sTrigger9, *sTrigger10,* lTrigger;

		RevoluteJoint* spinJoint,* joint1,* joint2;

		
	public:
		//specify your custom filter shader here
		//PxDefaultSimulationFilterShader by default
		MyScene() : Scene() {};
		bool launchReady, dead;
		int score, lives;
	

		///A custom scene class
		void SetVisualisation()
		{
			px_scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eACTOR_AXES, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eBODY_LIN_VELOCITY, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LIMITS, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LOCAL_FRAMES, 1.0f);

		}

		//Custom scene initialisation
		virtual void CustomInit() 
		{
			SetVisualisation();			

			GetMaterial()->setDynamicFriction(.2f);
			
			veryBouncy = CreateMaterial(0.f, 0.f, 3.f);
			bouncy = CreateMaterial(.0f, .0f, 1.f);
			notBouncy = CreateMaterial(.0f, .0f, .1f);
			zeroBounce = CreateMaterial(.0f, .0f, .0f);

			///Initialise and set the customised event callback
			my_callback = new MySimulationEventCallback();
			px_scene->setSimulationEventCallback(my_callback);


			//****************************************************************Barriers******************************************************
			//Backboard
			plane = new Plane();
			plane->Color(PxVec3(210.f/255.f,210.f/255.f,210.f/255.f));
			plane->Material(notBouncy);
			Add(plane);

			//Arena Walls
			sWall = new Walls(PxTransform(0.f, 3.f, 0.f));
			sWall->Color(PxVec3(64.f / 255.f, 64.f / 255.f, 64.f / 255.f));
			sWall->Material(notBouncy);
			Add(sWall);

			//Top Curved Wall
			cWall = new Wall2(PxTransform(0.f, 3.f, -63.f));
			cWall->Color(PxVec3(64.f / 255.f, 64.f / 255.f, 64.f / 255.f));
			cWall->Material(notBouncy);
			Add(cWall);

			//Top right interior curved wall
			sCWall1 = new sCWall(PxTransform(PxVec3(18.f, 3.f, -20.f), PxQuat(250 * PxPi / 180, PxVec3(0.f, 1.f, 0.f))));
			sCWall1->Color(PxVec3(64.f / 255.f, 64.f / 255.f, 64.f / 255.f));
			sCWall1->Material(notBouncy);
			Add(sCWall1);

			//Left group of curved walls
			gCWall1 = new sCWall2(PxTransform(PxVec3(-13.f, 3.f, 15.f), PxQuat(4.5378560552, PxVec3(0.f, 1.f, 0.f))));
			gCWall1->Color(PxVec3(64.f / 255.f, 64.f / 255.f, 64.f / 255.f));
			gCWall1->Material(notBouncy);
			Add(gCWall1);

			//***************************************************StationaryObjects*********************************************************
			//Bouncer group 1 (Top 5 bouncers)
			bouncer1 = new BouncerG1(PxTransform(PxVec3(10.f, 0.f, -40.f), PxQuat(PxPi / 2, PxVec3(0.f, 0.f, 1.f))));
			bouncer1->Color(PxVec3(0.f / 255.f, 255.f / 255.f, 255.f / 255.f));
			bouncer1->Material(veryBouncy);
			Add(bouncer1);

			//Bouncer group 2 (Mid 5 bouncers)
			bouncer2 = new BouncerG2(PxTransform(PxVec3(-15.f, 0.f, 10.f), PxQuat(PxPi / 2, PxVec3(0.f, 0.f, 1.f))));
			bouncer2->Color(PxVec3(0.f / 255.f, 255.f / 255.f, 255.f / 255.f));
			bouncer2->Material(veryBouncy);
			Add(bouncer2);



			//Bottom right Triangle
			triangle = new Triangle(PxTransform(PxVec3(17.f, 3.f, 30.f), PxQuat(4.1887902048, PxVec3(.0f, 1.f, .0f))));
			triangle->Color(PxVec3(178.f / 255.f, 102.f / 255.f, 255.f / 255.f));
			triangle->Material(notBouncy);
			Add(triangle);

			//Bottom left Triangle
			triangle1 = new Triangle(PxTransform(PxVec3(-17.f, 3.f, 30.f), PxQuat(-4.1887902048, PxVec3(.0f, 1.f, .0f))));
			triangle1->Color(PxVec3(178.f / 255.f, 102.f / 255.f, 255.f / 255.f));
			triangle1->Material(notBouncy);
			Add(triangle1);

			//Top right Triangle
			triangle2 = new Triangle(PxTransform(PxVec3(17.f, 3.f, -55.f), PxQuat(2.617993878, PxVec3(.0f, 1.f, .0f))));
			triangle2->Color(PxVec3(178.f / 255.f, 102.f / 255.f, 255.f / 255.f));
			triangle2->Material(notBouncy);
			Add(triangle2);

			//Top Left Triangle
			triangle3 = new Triangle(PxTransform(PxVec3(-20.f, 3.f, -28.f), PxQuat(2.5307274154, PxVec3(.0f, 1.f, .0f))));
			triangle3->Color(PxVec3(178.f / 255.f, 102.f / 255.f, 255.f / 255.f));
			triangle3->Material(notBouncy);
			Add(triangle3);

			//Top Central Triangle
			triangle4 = new Triangle(PxTransform(PxVec3(-8.f, 3.f, -50.f), PxQuat(PxPi / 3, PxVec3(.0f, 1.f, .0f))));
			triangle4->Color(PxVec3(178.f / 255.f, 102.f / 255.f, 255.f / 255.f));
			triangle4->Material(notBouncy);
			Add(triangle4);



			//Pins stopping paddles from over rotating
			pins = new Pin(PxTransform(PxVec3(0.f, .0f, 49.f)));
			pins->Color(PxVec3(0.f / 255.f, 0.f / 255.f, 0.f / 255.f));
			pins->Material(notBouncy);
			Add(pins);
			//*****************************************************************************************************************************
			
			//******************************************1st paddle system*******************************************************
			//Paddle 1
			paddle1 = new Paddle(PxTransform(PxVec3(-7.f, -.2f, 49.f)));
			paddle1->Color(PxVec3(1.f,0.f,0.f));
			paddle1->Material(notBouncy);
			paddle1->Name("Paddle1");
			Add(paddle1);

			//Joint For paddle
			joint1 = new RevoluteJoint(NULL, PxTransform(PxVec3(-10.5f, .5f, 45.5f), PxQuat(PxPi / 2, PxVec3(0.f, 0.f, 1.f))), paddle1, PxTransform(PxVec3(-4.25, 0.f, 0.f), PxQuat(PxPi / 2, PxVec3(0.f, 1.f, 0.f))));
			joint1->DriveVelocity(PxReal(-1));
			//joint1.SetLimits(0.785398, 4.88692);
			//*******************************************************************************************************************

			//******************************************2nd paddle system********************************************************
			//Paddle 2
			paddle2 = new Paddle(PxTransform(PxVec3(5.f, -.2f, 49.f), PxQuat(2.0943951024, PxVec3(1.f, 0.f, 0.f))));
			paddle2->Color(PxVec3(1.f, 0.f, 0.f));
			paddle2->Material(notBouncy);
			paddle2->Name("Paddle2");
			Add(paddle2);

			//Joint For paddle
			joint2 = new RevoluteJoint(NULL, PxTransform(PxVec3(7.f, 0.5f, 45.5f), PxQuat(PxPi / 2, PxVec3(0.f, 0.f, 1.f))), paddle2, PxTransform(PxVec3(4.25f, 0.f, 0.f), PxQuat(PxPi / 2, PxVec3(0.f, 1.f, 0.f))));
			joint2->DriveVelocity(PxReal(1));
			//joint2->SetLimits(0.785398, 4.88692);
			//*******************************************************************************************************************
			
			//******************************************Motor system*************************************************************
			//Arms for motor
			arms = new mArms(PxTransform(PxVec3(0.f, .5f, 0.f)));
			arms->Color(PxVec3(0.f, 1.f, 0.f));
			arms->GetShape()->getActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
			Add(arms);

			//Joint to spint object
			spinJoint = new RevoluteJoint(NULL, PxTransform(PxVec3(16.5f, 0.f, 15.f), PxQuat(PxPi / 2, PxVec3(0.f, 0.f, 1.f))), arms, PxTransform(PxVec3(0.f, 0.f, 0.f), PxQuat(PxPi / 2, PxVec3(0.f, 0.f, 1.f))));
			spinJoint->DriveVelocity(PxReal(-0.5));

			//*******************************************************************************************************************

			//*****************************************Triggers******************************************************************

			//Death Trigger
			dTrigger = new DeathTrigger(PxTransform(PxVec3(-1.5f, 1.f, 50.f)));
			dTrigger->Color(PxVec3(0.f / 255.f, 0.f / 255.f, 0.f / 255.f));
			dTrigger->SetTrigger(true);
			dTrigger->SetupFiltering(FilterGroup::DEATH, FilterGroup::PINBALL);
			dTrigger->Name("Death");
			
			Add(dTrigger);

			//*****Triggers for different score values******
			
			//********************+ 10 (BLUE)
			//Score pad between bumper and triangle top center 
			sTrigger1 = new ScoreTrigger(PxTransform(PxVec3(-5.f, -.8f, -45.f), PxQuat(PxPi, (PxVec3(0.f, 0.f, 1.f)))));
			sTrigger1->Color(PxVec3(100.f / 255.f, 100.f / 255.f, 255.f / 255.f));
			sTrigger1->SetTrigger(true);
			sTrigger1->SetupFiltering(FilterGroup::SCORE1, FilterGroup::PINBALL);
			sTrigger1->Name("Score10");
			
			Add(sTrigger1);
			
			//Score pad mid left of arena
			sTrigger2 = new ScoreTrigger(PxTransform(PxVec3(-15.f, -.8f, -1.f), PxQuat(PxPi, (PxVec3(0.f, 0.f, 1.f)))));
			sTrigger2->Color(PxVec3(100.f / 255.f, 100.f / 255.f, 255.f / 255.f));
			sTrigger2->SetTrigger(true);
			sTrigger2->SetupFiltering(FilterGroup::SCORE1, FilterGroup::PINBALL);
			sTrigger2->Name("Score10");

			Add(sTrigger2);
			//**************************

			//********************+ 50 (ORANGE)
			//Score pad at top right of arena
			sTrigger3 = new ScoreTrigger(PxTransform(PxVec3(10.f, -.8f, -58.f), PxQuat(PxPi, (PxVec3(0.f, 0.f, 1.f)))));
			sTrigger3->Color(PxVec3(255.f / 255.f, 178.f / 255.f, 102.f / 255.f));
			sTrigger3->SetTrigger(true);
			sTrigger3->SetupFiltering(FilterGroup::SCORE1, FilterGroup::PINBALL);
			sTrigger3->Name("Score50");

			Add(sTrigger3);

			//Score pad mid left arean between 3 bouncers
			sTrigger4 = new ScoreTrigger(PxTransform(PxVec3(-20.f, -.8f, 10.f), PxQuat(PxPi, (PxVec3(0.f, 0.f, 1.f)))));
			sTrigger4->Color(PxVec3(255.f / 255.f, 178.f / 255.f, 102.f / 255.f));
			sTrigger4->SetTrigger(true);
			sTrigger4->SetupFiltering(FilterGroup::SCORE1, FilterGroup::PINBALL);
			sTrigger4->Name("Score50");

			Add(sTrigger4);

			//Score pad beneath rotating arms mid right arena
			sTrigger5 = new ScoreTrigger(PxTransform(PxVec3(17.f, -.8f, 20.f), PxQuat(PxPi, (PxVec3(0.f, 0.f, 1.f)))));
			sTrigger5->Color(PxVec3(255.f / 255.f, 178.f / 255.f, 102.f / 255.f));
			sTrigger5->SetTrigger(true);
			sTrigger5->SetupFiltering(FilterGroup::SCORE1, FilterGroup::PINBALL);
			sTrigger5->Name("Score50");

			Add(sTrigger5);

			//Score pad top left corner of arena
			sTrigger6 = new ScoreTrigger(PxTransform(PxVec3(-22.f, -.8f, -50.f), PxQuat(PxPi, (PxVec3(0.f, 0.f, 1.f)))));
			sTrigger6->Color(PxVec3(255.f / 255.f, 178.f / 255.f, 102.f / 255.f));
			sTrigger6->SetTrigger(true);
			sTrigger6->SetupFiltering(FilterGroup::SCORE1, FilterGroup::PINBALL);
			sTrigger6->Name("Score50");

			Add(sTrigger6);
			//**************************
			
			//********************+ 100 (GOLD)
			//Score pad between group of 4 bouncers top center
			sTrigger7 = new ScoreTrigger(PxTransform(PxVec3(3.f, -.8f, -38.f)));
			sTrigger7->Color(PxVec3(210.f / 255.f, 210.f / 255.f, 0.f / 255.f));
			sTrigger7->SetTrigger(true);
			sTrigger7->SetupFiltering(FilterGroup::SCORE2, FilterGroup::PINBALL);
			sTrigger7->Name("Score100");
			
			Add(sTrigger7);

			//Score pad between right curved wall and pinball shoot
			sTrigger8 = new ScoreTrigger(PxTransform(PxVec3(20.5f, -.8f, -25.f)));
			sTrigger8->Color(PxVec3(210.f / 255.f, 210.f / 255.f, 0.f / 255.f));
			sTrigger8->SetTrigger(true);
			sTrigger8->SetupFiltering(FilterGroup::SCORE3, FilterGroup::PINBALL);
			sTrigger8->Name("Score100");

			Add(sTrigger8);

			//Score pad bottom left of arena
			sTrigger9 = new ScoreTrigger(PxTransform(PxVec3(-22.f, -.8f, 25.f)));
			sTrigger9->Color(PxVec3(210.f / 255.f, 210.f / 255.f, 0.f / 255.f));
			sTrigger9->SetTrigger(true);
			sTrigger9->SetupFiltering(FilterGroup::SCORE3, FilterGroup::PINBALL);
			sTrigger9->Name("Score100");

			Add(sTrigger9);

			//Score pad top left of arena between bouncer and triangle
			sTrigger10 = new ScoreTrigger(PxTransform(PxVec3(-12.f, -.8f, -49.f)));
			sTrigger10->Color(PxVec3(210.f / 255.f, 210.f / 255.f, 0.f / 255.f));
			sTrigger10->SetTrigger(true);
			sTrigger10->SetupFiltering(FilterGroup::SCORE3, FilterGroup::PINBALL);
			sTrigger10->Name("Score100");

			Add(sTrigger10);
			//******************************

			//Trigger responsible for the launching of the pin ball
			lTrigger = new ScoreTrigger(PxTransform(PxVec3(23.f, -.8f, 48.f), PxQuat(PxPi/2, (PxVec3(1.f, 0.f, 0.f)))));
			lTrigger->Color(PxVec3(210.f / 255.f, 210.f / 255.f, 210.f / 255.f));
			lTrigger->SetTrigger(true);
			lTrigger->SetupFiltering(FilterGroup::SCORE4, FilterGroup::PINBALL);
			
			Add(lTrigger);

			//********************************************************************************************************************

			//****************************************************************PinBall******************************************************
			//Pinball
			ball = new Sphere(PxTransform(23.f, 0.f, 44.f));
			ball->Color(PxVec3(255.f / 255.f, 51.f / 255.f, 255.f / 255.f));
			ball->Material(bouncy);
			ball->Name("PinBall");
			ball->SetupFiltering(FilterGroup::PINBALL, FilterGroup::DEATH | FilterGroup::SCORE1 | FilterGroup::SCORE2 | FilterGroup::SCORE3 | FilterGroup::SCORE4 | FilterGroup::LAUNCH);
			Add(ball);

			if (dead == true)
			{
				Add(ball);
			}
			//******************************************************************************************************************************

			
		}

		//Custom udpate function
		virtual void CustomUpdate() 
		{
			dead = my_callback->deathTrigger;
			launchReady = my_callback->launchTrigger;
			score = my_callback->score;
			lives = my_callback->lives;

		}

		/// An example use of key release handling
		void ExampleKeyReleaseHandler()
		{
			cerr << "I am realeased!" << endl;
		}

		/// An example use of key presse handling
		void ExampleKeyPressHandler()
		{
			cerr << "I am pressed!" << endl;
		}
	};
}
