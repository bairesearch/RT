/*******************************************************************************
 *
 * File Name: LDreferenceClass.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2012 Baxter AI (baxterai.com)
 * Project: Generic Ldraw Construct Functions
 * Project Version: 3a7a 06-June-2012
 *
 *******************************************************************************/



/*LDreferenceClass.cpp: Defines a class for references to submodels/parts/units within a scene file*/

#include "LDreferenceClass.h"



Reference::Reference(void)
{
	//Define default values for Reference

	relativePosition.x = 0.0;
	relativePosition.y = 0.0;
	relativePosition.z = 0.0;

	absolutePosition.x = 0.0;
	absolutePosition.y = 0.0;
	absolutePosition.z = 0.0;

		//deformationMatrix initialisations here are required for bcc32 compiler
	deformationMatrix.a.x = 1.0;
	deformationMatrix.a.y = 0.0;
	deformationMatrix.a.z = 0.0;
	deformationMatrix.b.x = 0.0;
	deformationMatrix.b.y = 1.0;
	deformationMatrix.b.z = 0.0;
	deformationMatrix.c.x = 0.0;
	deformationMatrix.c.y = 0.0;
	deformationMatrix.c.z = 1.0;

	absoluteDeformationMatrix.a.x = 1.0;
	absoluteDeformationMatrix.a.y = 0.0;
	absoluteDeformationMatrix.a.z = 0.0;
	absoluteDeformationMatrix.b.x = 0.0;
	absoluteDeformationMatrix.b.y = 1.0;
	absoluteDeformationMatrix.b.z = 0.0;
	absoluteDeformationMatrix.c.x = 0.0;
	absoluteDeformationMatrix.c.y = 0.0;
	absoluteDeformationMatrix.c.z = 1.0;

	colour = 0;
	name = "";
	next = NULL;
	isSubModelReference = false;

#ifdef USE_LD_ABSOLUTE_COLOUR
	absoluteColour = DAT_FILE_DEFAULT_COLOUR;
#endif

		/*new parameters added to parseFile() 18-mar-07*/
	vertex1relativePosition.x = 0.0;
	vertex1relativePosition.y = 0.0;
	vertex1relativePosition.z = 0.0;
	vertex2relativePosition.x = 0.0;
	vertex2relativePosition.y = 0.0;
	vertex2relativePosition.z = 0.0;
	vertex3relativePosition.x = 0.0;
	vertex3relativePosition.y = 0.0;
	vertex3relativePosition.z = 0.0;
	vertex4relativePosition.x = 0.0;
	vertex4relativePosition.y = 0.0;
	vertex4relativePosition.z = 0.0;
	vertex1absolutePosition.x = 0.0;
	vertex1absolutePosition.y = 0.0;
	vertex1absolutePosition.z = 0.0;
	vertex2absolutePosition.x = 0.0;
	vertex2absolutePosition.y = 0.0;
	vertex2absolutePosition.z = 0.0;
	vertex3absolutePosition.x = 0.0;
	vertex3absolutePosition.y = 0.0;
	vertex3absolutePosition.z = 0.0;
	vertex4absolutePosition.x = 0.0;
	vertex4absolutePosition.y = 0.0;
	vertex4absolutePosition.z = 0.0;

	vertex1absolutePositionBackup.x = 0.0;
	vertex1absolutePositionBackup.y = 0.0;
	vertex1absolutePositionBackup.z = 0.0;
	vertex2absolutePositionBackup.x = 0.0;
	vertex2absolutePositionBackup.y = 0.0;
	vertex2absolutePositionBackup.z = 0.0;
	vertex3absolutePositionBackup.x = 0.0;
	vertex3absolutePositionBackup.y = 0.0;
	vertex3absolutePositionBackup.z = 0.0;
	vertex4absolutePositionBackup.x = 0.0;
	vertex4absolutePositionBackup.y = 0.0;
	vertex4absolutePositionBackup.z = 0.0;
	referenceEnabledMethod2DOD = true;

	type = REFERENCE_TYPE_UNDEFINED;

	/*Additional values used with recursive parser*/
#ifdef USE_LRRC
	subModelDetails = NULL;
#endif
	firstReferenceWithinSubModel = NULL;


	/*cout << "\nA Reference object was Constructed\n" << endl;*/
}

Reference::~Reference()
{
	//int i = 0;

	Reference* n = this->next;
	Reference* nn = NULL;
	while(n != NULL)
	{
		nn = n->next;

		//cout << "deleteing reference i=" << i << endl;
		//i++;
	#ifdef USE_LRRC
		if(n->subModelDetails != NULL)
		{
			delete n->subModelDetails;
		}
	#endif
		if(n->firstReferenceWithinSubModel != NULL)
		{
			delete n->firstReferenceWithinSubModel;
		}

		n->next = NULL;
		delete n;
		n = nn;
	}


#ifdef USE_LRRC
	if(this->subModelDetails != NULL)
	{
		delete this->subModelDetails;
	}
#endif
	if(this->firstReferenceWithinSubModel != NULL)
	{
		delete this->firstReferenceWithinSubModel;
	}


	nn = NULL;
	n = NULL;


}



Reference::Reference(string referenceName, int referenceColour, bool createNewSubmodel)
{
	//Define default values for Reference

	relativePosition.x = 0.0;
	relativePosition.y = 0.0;
	relativePosition.z = 0.0;

	absolutePosition.x = 0.0;
	absolutePosition.y = 0.0;
	absolutePosition.z = 0.0;

		//deformationMatrix initialisations here are required for bcc32 compiler
	deformationMatrix.a.x = 1.0;
	deformationMatrix.a.y = 0.0;
	deformationMatrix.a.z = 0.0;
	deformationMatrix.b.x = 0.0;
	deformationMatrix.b.y = 1.0;
	deformationMatrix.b.z = 0.0;
	deformationMatrix.c.x = 0.0;
	deformationMatrix.c.y = 0.0;
	deformationMatrix.c.z = 1.0;

	absoluteDeformationMatrix.a.x = 1.0;
	absoluteDeformationMatrix.a.y = 0.0;
	absoluteDeformationMatrix.a.z = 0.0;
	absoluteDeformationMatrix.b.x = 0.0;
	absoluteDeformationMatrix.b.y = 1.0;
	absoluteDeformationMatrix.b.z = 0.0;
	absoluteDeformationMatrix.c.x = 0.0;
	absoluteDeformationMatrix.c.y = 0.0;
	absoluteDeformationMatrix.c.z = 1.0;


	colour = referenceColour;
	name = referenceName;
	next = NULL;
	isSubModelReference = false;

#ifdef USE_RT
	absoluteColour = DAT_FILE_DEFAULT_COLOUR;
#endif

		/*new parameters added to parseFile() 18-mar-07*/
	vertex1relativePosition.x = 0.0;
	vertex1relativePosition.y = 0.0;
	vertex1relativePosition.z = 0.0;
	vertex2relativePosition.x = 0.0;
	vertex2relativePosition.y = 0.0;
	vertex2relativePosition.z = 0.0;
	vertex3relativePosition.x = 0.0;
	vertex3relativePosition.y = 0.0;
	vertex3relativePosition.z = 0.0;
	vertex4relativePosition.x = 0.0;
	vertex4relativePosition.y = 0.0;
	vertex4relativePosition.z = 0.0;
	vertex1absolutePosition.x = 0.0;
	vertex1absolutePosition.y = 0.0;
	vertex1absolutePosition.z = 0.0;
	vertex2absolutePosition.x = 0.0;
	vertex2absolutePosition.y = 0.0;
	vertex2absolutePosition.z = 0.0;
	vertex3absolutePosition.x = 0.0;
	vertex3absolutePosition.y = 0.0;
	vertex3absolutePosition.z = 0.0;
	vertex4absolutePosition.x = 0.0;
	vertex4absolutePosition.y = 0.0;
	vertex4absolutePosition.z = 0.0;

	vertex1absolutePositionBackup.x = 0.0;
	vertex1absolutePositionBackup.y = 0.0;
	vertex1absolutePositionBackup.z = 0.0;
	vertex2absolutePositionBackup.x = 0.0;
	vertex2absolutePositionBackup.y = 0.0;
	vertex2absolutePositionBackup.z = 0.0;
	vertex3absolutePositionBackup.x = 0.0;
	vertex3absolutePositionBackup.y = 0.0;
	vertex3absolutePositionBackup.z = 0.0;
	vertex4absolutePositionBackup.x = 0.0;
	vertex4absolutePositionBackup.y = 0.0;
	vertex4absolutePositionBackup.z = 0.0;
	referenceEnabledMethod2DOD = true;

	type = REFERENCE_TYPE_UNDEFINED;

	/*Additional values used with recursive parser*/


	if(createNewSubmodel)
	{
		#ifdef USE_LRRC
		subModelDetails = new ModelDetails();
		#endif
		firstReferenceWithinSubModel = NULL;
	}
	else
	{
		#ifdef USE_LRRC
		subModelDetails = NULL;
		#endif
		firstReferenceWithinSubModel = NULL;
	}


	/*cout << "\nA Reference object was Constructed\n" << endl;*/
}



Reference::Reference(bool createNewSubmodel)
{
	//Define default values for Reference

	relativePosition.x = 0.0;
	relativePosition.y = 0.0;
	relativePosition.z = 0.0;

	absolutePosition.x = 0.0;
	absolutePosition.y = 0.0;
	absolutePosition.z = 0.0;

		//deformationMatrix initialisations here are required for bcc32 compiler
	deformationMatrix.a.x = 1.0;
	deformationMatrix.a.y = 0.0;
	deformationMatrix.a.z = 0.0;
	deformationMatrix.b.x = 0.0;
	deformationMatrix.b.y = 1.0;
	deformationMatrix.b.z = 0.0;
	deformationMatrix.c.x = 0.0;
	deformationMatrix.c.y = 0.0;
	deformationMatrix.c.z = 1.0;

	absoluteDeformationMatrix.a.x = 1.0;
	absoluteDeformationMatrix.a.y = 0.0;
	absoluteDeformationMatrix.a.z = 0.0;
	absoluteDeformationMatrix.b.x = 0.0;
	absoluteDeformationMatrix.b.y = 1.0;
	absoluteDeformationMatrix.b.z = 0.0;
	absoluteDeformationMatrix.c.x = 0.0;
	absoluteDeformationMatrix.c.y = 0.0;
	absoluteDeformationMatrix.c.z = 1.0;

	colour = 0;
	name = "";
	next = NULL;

#ifdef USE_RT
	absoluteColour = DAT_FILE_DEFAULT_COLOUR;
#endif

	isSubModelReference = false;

		/*new parameters added to parseFile() 18-mar-07*/
	vertex1relativePosition.x = 0.0;
	vertex1relativePosition.y = 0.0;
	vertex1relativePosition.z = 0.0;
	vertex2relativePosition.x = 0.0;
	vertex2relativePosition.y = 0.0;
	vertex2relativePosition.z = 0.0;
	vertex3relativePosition.x = 0.0;
	vertex3relativePosition.y = 0.0;
	vertex3relativePosition.z = 0.0;
	vertex4relativePosition.x = 0.0;
	vertex4relativePosition.y = 0.0;
	vertex4relativePosition.z = 0.0;
	vertex1absolutePosition.x = 0.0;
	vertex1absolutePosition.y = 0.0;
	vertex1absolutePosition.z = 0.0;
	vertex2absolutePosition.x = 0.0;
	vertex2absolutePosition.y = 0.0;
	vertex2absolutePosition.z = 0.0;
	vertex3absolutePosition.x = 0.0;
	vertex3absolutePosition.y = 0.0;
	vertex3absolutePosition.z = 0.0;
	vertex4absolutePosition.x = 0.0;
	vertex4absolutePosition.y = 0.0;
	vertex4absolutePosition.z = 0.0;

	vertex1absolutePositionBackup.x = 0.0;
	vertex1absolutePositionBackup.y = 0.0;
	vertex1absolutePositionBackup.z = 0.0;
	vertex2absolutePositionBackup.x = 0.0;
	vertex2absolutePositionBackup.y = 0.0;
	vertex2absolutePositionBackup.z = 0.0;
	vertex3absolutePositionBackup.x = 0.0;
	vertex3absolutePositionBackup.y = 0.0;
	vertex3absolutePositionBackup.z = 0.0;
	vertex4absolutePositionBackup.x = 0.0;
	vertex4absolutePositionBackup.y = 0.0;
	vertex4absolutePositionBackup.z = 0.0;
	referenceEnabledMethod2DOD = true;

	type = REFERENCE_TYPE_UNDEFINED;

	/*Additional values used with recursive parser*/

	if(createNewSubmodel)
	{
		#ifdef USE_LRRC
		subModelDetails = new ModelDetails();
		#endif
		firstReferenceWithinSubModel = NULL;
	}
	else
	{
		#ifdef USE_LRRC
		subModelDetails = NULL;
		#endif
		firstReferenceWithinSubModel = NULL;
	}



	/*cout << "\nA Reference object was Constructed\n" << endl;*/
}

void copyReferencePosition(Reference * r, Reference * referenceToCopy)
{
	r->relativePosition.x = referenceToCopy->relativePosition.x;
	r->relativePosition.y = referenceToCopy->relativePosition.y;
	r->relativePosition.z = referenceToCopy->relativePosition.z;
	r->absolutePosition.x = referenceToCopy->absolutePosition.x;
	r->absolutePosition.y = referenceToCopy->absolutePosition.y;
	r->absolutePosition.z = referenceToCopy->absolutePosition.z;
}



int obtainReferencePlayerID(Reference * referenceInThisPhaseStartSceneFile)
{
	#ifdef GAME_USE_FILENAME_AS_UNIQUE_UNIT_IDS
	return referenceInThisPhaseStartSceneFile->colour;
	#endif
	#ifdef GAME_USE_COLOUR_AS_UNIQUE_UNIT_IDS
	return (referenceInThisPhaseStartSceneFile->colour)%10;		//Eg the player ID is the least significant bits
	#endif

	return 1;
}

void convertLdrawColourToDatFileRGB(int dataFileColour, colour * col)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	
	if(dataFileColour == DAT_FILE_COLOUR_BLACK)
	{
		r = DAT_FILE_COLOUR_BLACK_RGB_R;
		g = DAT_FILE_COLOUR_BLACK_RGB_G;
		b = DAT_FILE_COLOUR_BLACK_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_BLUE)
	{
		r = DAT_FILE_COLOUR_BLUE_RGB_R;
		g = DAT_FILE_COLOUR_BLUE_RGB_G;
		b = DAT_FILE_COLOUR_BLUE_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_GREEN)
	{
		r = DAT_FILE_COLOUR_GREEN_RGB_R;
		g = DAT_FILE_COLOUR_GREEN_RGB_G;
		b = DAT_FILE_COLOUR_GREEN_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_CYAN)
	{
		r = DAT_FILE_COLOUR_CYAN_RGB_R;
		g = DAT_FILE_COLOUR_CYAN_RGB_G;
		b = DAT_FILE_COLOUR_CYAN_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_RED)
	{
		r = DAT_FILE_COLOUR_RED_RGB_R;
		g = DAT_FILE_COLOUR_RED_RGB_G;
		b = DAT_FILE_COLOUR_RED_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_MAGENTA)
	{
		r = DAT_FILE_COLOUR_MAGENTA_RGB_R;
		g = DAT_FILE_COLOUR_MAGENTA_RGB_G;
		b = DAT_FILE_COLOUR_MAGENTA_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_BROWN)
	{
		r = DAT_FILE_COLOUR_BROWN_RGB_R;
		g = DAT_FILE_COLOUR_BROWN_RGB_G;
		b = DAT_FILE_COLOUR_BROWN_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_LIGHTGREY)
	{
		r = DAT_FILE_COLOUR_LIGHTGREY_RGB_R;
		g = DAT_FILE_COLOUR_LIGHTGREY_RGB_G;
		b = DAT_FILE_COLOUR_LIGHTGREY_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_DARKGREY)
	{
		r = DAT_FILE_COLOUR_DARKGREY_RGB_R;
		g = DAT_FILE_COLOUR_DARKGREY_RGB_G;
		b = DAT_FILE_COLOUR_DARKGREY_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_YELLOW)
	{
		r = DAT_FILE_COLOUR_YELLOW_RGB_R;
		g = DAT_FILE_COLOUR_YELLOW_RGB_G;
		b = DAT_FILE_COLOUR_YELLOW_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_WHITE)
	{
		r = DAT_FILE_COLOUR_WHITE_RGB_R;
		g = DAT_FILE_COLOUR_WHITE_RGB_G;
		b = DAT_FILE_COLOUR_WHITE_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_ORANGE)
	{
		r = DAT_FILE_COLOUR_ORANGE_RGB_R;
		g = DAT_FILE_COLOUR_ORANGE_RGB_G;
		b = DAT_FILE_COLOUR_ORANGE_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_PURPLE)
	{
		r = DAT_FILE_COLOUR_PURPLE_RGB_R;
		g = DAT_FILE_COLOUR_PURPLE_RGB_G;
		b = DAT_FILE_COLOUR_PURPLE_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_DARKBLUE)
	{
		r = DAT_FILE_COLOUR_DARKBLUE_RGB_R;
		g = DAT_FILE_COLOUR_DARKBLUE_RGB_G;
		b = DAT_FILE_COLOUR_DARKBLUE_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_DARKGREEN)
	{
		r = DAT_FILE_COLOUR_DARKGREEN_RGB_R;
		g = DAT_FILE_COLOUR_DARKGREEN_RGB_G;
		b = DAT_FILE_COLOUR_DARKGREEN_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_DARKRED)
	{
		r = DAT_FILE_COLOUR_DARKRED_RGB_R;
		g = DAT_FILE_COLOUR_DARKRED_RGB_G;
		b = DAT_FILE_COLOUR_DARKRED_RGB_B;
	}
	else if(dataFileColour == DAT_FILE_COLOUR_AQUA)
	{			
		r = DAT_FILE_COLOUR_AQUA_RGB_R;
		g = DAT_FILE_COLOUR_AQUA_RGB_G;
		b = DAT_FILE_COLOUR_AQUA_RGB_B;
	}		
	else
	{
		cout << "invalid dat file colour for conversion to RGB" << endl;
		exit(0);
	}

	col->r = r;
	col->g = g;
	col->b = b;

}




