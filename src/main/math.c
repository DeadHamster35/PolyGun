#include <nusys.h>
#include <nualsgi_n.h>
#include "main.h"
#include "math.h"
extern float sintable[];
extern float costable[];
extern short atntable[];

AffineMtx GlobalAffine;

float sint(ushort angle)
{
	return(sintable[angle>>4]);
}
float cost(ushort angle)
{
	return(costable[angle>>4]);    
}

ushort atant(float a, float b)
{
	ushort angle;
	float  ans;
	if (b == 0.0f)
    {
        return atntable[0];
    }
    else 
    {
        ans=a/b;
        if(ans>1000000)    
        {
            if(a>0)
            {
                return (DEG1 * 90);
            }
            else
            {
                return (DEG1 * -90);
            }     
        }
        else	  
        {
            
            return atntable[(int)(ans * 1024.0f + 0.5f)];
        }
        
    }
	return 0;
    return atntable[0];
}

typedef union {
	long	word;
	short	half[2];
	char	byte[4];	
} SPacked;


ushort atan2(float y, float x)
{
	ushort angle;
	if (y >= 0) 
    {
		if (x >= 0) 
        {
			if (x >= y)
            {
                return ((DEG1 * 0) + atant(y,x));
            }
            else
            {
                return ((DEG1 * 90) - atant(x,y));
            }
		}
		else 
        {
			x = -x;

			if (x < y)
            {
                return ((DEG1 * 90) + atant(x,y));
            }
            else
            {
                return ((DEG1 * 180) - atant(y,x));
            }
		}
	}
	else 
    {
		y = -y;

		if (x < 0) 
        {
			x = -x;

			if (x >= y)
            {
                return ((DEG1 * 180) + atant(y, x));
            } 
            else
            {
                return ((DEG1 * 270) - atant(x, y));
            }
		}
		else 
        {
			if (x < y)
            {
                return ((DEG1 * 270) + atant(x, y));
            }
            else
            {
                return ((DEG1 * 360) - atant(y, x));
            }
		}
	}
    
    
    return ((DEG1 * 0) - atant(x, y));
}


void AffineToMtx(Mtx *Matrix, AffineMtx Affine)
{	
	SPacked data;
	register int	count;
	register short	*integer  = (short *)&(Matrix->m[0][0]);
	register short	*fraction = (short *)&(Matrix->m[2][0]);
	register float	*real	  = (float *)&(Affine[0][0]);
    

	for (count = 0; count < 16; count++) {
		data.word	= (long)((*real++) * 65536.0f);
		*integer++  = data.half[0];
		*fraction++ = data.half[1];
	}
}


void CreateModelMatrix(AffineMtx Matrix, Vector Position, SVector Angle)
{
    float sinA = sint(Angle[0]);
    float cosA = cost(Angle[0]);
    float sinB = sint(Angle[1]);
    float cosB = cost(Angle[1]);
    float sinC = sint(Angle[2]);
    float cosC = cost(Angle[2]);

    Matrix[0][0] =  cosB * cosC + sinA * sinB * sinC;
    Matrix[1][0] = -cosB * sinC + sinA * sinB * cosC;
    Matrix[2][0] =  cosA * sinB;
    Matrix[3][0] =  (float)Position[0];
               
    Matrix[0][1] =  cosA * sinC;
    Matrix[1][1] =  cosA * cosC;
    Matrix[2][1] = -sinA;
    Matrix[3][1] =  (float)Position[1];
               
    Matrix[0][2] = -sinB * cosC + sinA * cosB * sinC;
    Matrix[1][2] =  sinB * sinC + sinA * cosB * cosC;
    Matrix[2][2] =  cosA * cosB;
    Matrix[3][2] =  (float)Position[2];
               
    Matrix[0][3] = 0.0f;
    Matrix[1][3] = 0.0f;
    Matrix[2][3] = 0.0f;
    Matrix[3][3] = 1.0f;
}


void CreateModelMatrixS(AffineMtx Matrix, SVector Position, SVector Angle)
{
    float sinA = sint(Angle[0]);
    float cosA = cost(Angle[0]);
    float sinB = sint(Angle[1]);
    float cosB = cost(Angle[1]);
    float sinC = sint(Angle[2]);
    float cosC = cost(Angle[2]);

    Matrix[0][0] =  cosB * cosC + sinA * sinB * sinC;
    Matrix[1][0] = -cosB * sinC + sinA * sinB * cosC;
    Matrix[2][0] =  cosA * sinB;
    Matrix[3][0] =  (float)Position[0];
               
    Matrix[0][1] =  cosA * sinC;
    Matrix[1][1] =  cosA * cosC;
    Matrix[2][1] = -sinA;
    Matrix[3][1] =  (float)Position[1];
               
    Matrix[0][2] = -sinB * cosC + sinA * cosB * sinC;
    Matrix[1][2] =  sinB * sinC + sinA * cosB * cosC;
    Matrix[2][2] =  cosA * cosB;
    Matrix[3][2] =  (float)Position[2];
               
    Matrix[0][3] = 0.0f;
    Matrix[1][3] = 0.0f;
    Matrix[2][3] = 0.0f;
    Matrix[3][3] = 1.0f;
}

void CreateModelMatrixZ(AffineMtx Matrix, Vector Position, SVector Angle) 
{

    float cosRoll = cost(Angle[0]);
    float sinRoll = sint(Angle[0]);
    float cosPitch = cost(Angle[1]);
    float sinPitch = sint(Angle[1]);
    float cosYaw = cost(Angle[2]);
    float sinYaw = sint(Angle[2]);  


    // Construct rotation matrix
    Matrix[0][0] = cosYaw * cosPitch;
    Matrix[0][1] = cosYaw * sinPitch * sinRoll - sinYaw * cosRoll;
    Matrix[0][2] = cosYaw * sinPitch * cosRoll + sinYaw * sinRoll;
    Matrix[0][3] = 0.0f;

    Matrix[1][0] = sinYaw * cosPitch;
    Matrix[1][1] = sinYaw * sinPitch * sinRoll + cosYaw * cosRoll;
    Matrix[1][2] = sinYaw * sinPitch * cosRoll - cosYaw * sinRoll;
    Matrix[1][3] = 0.0f;

    Matrix[2][0] = -sinPitch;
    Matrix[2][1] = cosPitch * sinRoll;
    Matrix[2][2] = cosPitch * cosRoll;
    Matrix[2][3] = 0.0f;

    Matrix[3][0] = Position[0];
    Matrix[3][1] = Position[1];
    Matrix[3][2] = Position[2];
    Matrix[3][3] = 1.0f;
}

void ScalingMatrix(AffineMtx matrix , float scale)
{
    matrix[0][0] *=  scale;
    matrix[1][0] *=  scale;
    matrix[2][0] *=  scale;
                    
    matrix[0][1] *=  scale;
    matrix[1][1] *=  scale;
    matrix[2][1] *=  scale;
                    
    matrix[0][2] *=  scale;
    matrix[1][2] *=  scale;
    matrix[2][2] *=  scale;
}


void ScaleMatrixXYZFixed(AffineMtx Matrix, SVector FScale)
{
    Matrix[0][0] *= (float)(FScale[0] / 100.0f);
    Matrix[1][0] *= (float)(FScale[0] / 100.0f);
    Matrix[2][0] *= (float)(FScale[0] / 100.0f);
    Matrix[1][0] *= (float)(FScale[1] / 100.0f);
    Matrix[1][1] *= (float)(FScale[1] / 100.0f);
    Matrix[1][2] *= (float)(FScale[1] / 100.0f);
    Matrix[2][0] *= (float)(FScale[2] / 100.0f);
    Matrix[2][1] *= (float)(FScale[2] / 100.0f);
    Matrix[2][2] *= (float)(FScale[2] / 100.0f);
}

extern void TransformMatrix(AffineMtx InputMatrix, Vector Position, Vector Look, Vector Up)
{
    float len;
    float xUp	, yUp	, zUp	;
    float xLook , yLook , zLook ;
    float xRight, yRight, zRight;

    xUp = Up[0];
    yUp = Up[1];
    zUp = Up[2];

    xLook = Look[0] - Position[0];
    yLook = Look[1] - Position[1];
    zLook = Look[2] - Position[2];
    len = -1.0 / sqrtf (xLook*xLook + yLook*yLook + zLook*zLook);
    xLook *= len;
    yLook *= len;
    zLook *= len;

    /* Right = Up x Look */

    xRight = yUp * zLook - zUp * yLook;
    yRight = zUp * xLook - xUp * zLook;
    zRight = xUp * yLook - yUp * xLook;
    len = 1.0 / sqrtf (xRight*xRight + yRight*yRight + zRight*zRight);
    xRight *= len;
    yRight *= len;
    zRight *= len;

    /* Up = Look x Right */

    xUp = yLook * zRight - zLook * yRight;
    yUp = zLook * xRight - xLook * zRight;
    zUp = xLook * yRight - yLook * xRight;
    len = 1.0 / sqrtf (xUp*xUp + yUp*yUp + zUp*zUp);
    xUp *= len;
    yUp *= len;
    zUp *= len;

    InputMatrix[0][0] = xRight;
    InputMatrix[1][0] = yRight;
    InputMatrix[2][0] = zRight;
    InputMatrix[3][0] = -((float)Position[0] * xRight + (float)Position[1] * yRight + (float)Position[2] * zRight);

    InputMatrix[0][1] = xUp;
    InputMatrix[1][1] = yUp;
    InputMatrix[2][1] = zUp;
    InputMatrix[3][1] = -((float)Position[0] * xUp + (float)Position[1] * yUp + (float)Position[2] * zUp);

    InputMatrix[0][2] = xLook;
    InputMatrix[1][2] = yLook;
    InputMatrix[2][2] = zLook;
    InputMatrix[3][2] = -((float)Position[0] * xLook + (float)Position[1] * yLook + (float)Position[2] * zLook);

    InputMatrix[0][3] = 0.0f;
    InputMatrix[1][3] = 0.0f;
    InputMatrix[2][3] = 0.0f;
    InputMatrix[3][3] = 1.0f;
}

float GetDistance(Vector A, Vector B)
{
    float Distance = 
    (
        ((A[0] - B[0]) * (A[0] - B[0])) +
        ((A[1] - B[1]) * (A[1] - B[1])) +
        ((A[2] - B[2]) * (A[2] - B[2]))
    );
    return sqrtf(Distance);
}


short GetDirection(Vector A, Vector B)
{
    return (-1 * atan2((B[0] - A[0]),(B[1] - A[1])));
}


void NormalizeVector(Vector vector)
{
	float V=sqrtf(vector[0]*vector[0]+vector[1]*vector[1]+vector[2]*vector[2]);
   	vector[0]=vector[0]/V;
   	vector[1]=vector[1]/V;
   	vector[2]=vector[2]/V;
}

void AlignZVector(Vector vect, short RotZ)
{
    float sine = sint(RotZ);
    float cosine = cost(RotZ);
    float v0 = vect[0];
    float v1 = vect[1];
    float v2 = vect[2];

    // Rotate around Z-axis (assuming Z-up)
    vect[0] = cosine * v0 - sine * v1;
    vect[1] = sine * v0 + cosine * v1;
    vect[2] = v2;
}


void AlignXVector(Vector vect, short RotX)
{
    float sine = sint(RotX);
    float cosine = cost(RotX);
    float v0 = vect[0];
    float v1 = vect[1];
    float v2 = vect[2];

    // Rotate around X-axis (assuming Z-up)
    vect[1] = cosine * v1 - sine * v2;
    vect[2] = sine * v1 + cosine * v2;
    vect[0] = v0;
}

void AlignYVector(Vector vect, short RotY)
{
    float sine = sint(RotY);
    float cosine = cost(RotY);
    float v0 = vect[0];
    float v1 = vect[1];
    float v2 = vect[2];

    // Rotate around Y-axis (assuming Z-up)
    vect[0] = cosine * v0 + sine * v2;
    vect[2] = -sine * v0 + cosine * v2;
    vect[1] = v1;
}




unsigned short	HiddenSeed;


unsigned short Random()
{
	unsigned	short	work;
	unsigned	short	work2;
	float		random;

	if ( HiddenSeed == 0x560a ) HiddenSeed = 0;

	work 		= (( HiddenSeed & 0xff) << 8 );
	work 		= 	 work ^ HiddenSeed;
	HiddenSeed = (( work & 0xff ) << 8 ) + (( work & 0xff00 ) >> 8 );
	work 		= (( work & 0xff ) << 1 ) ^ HiddenSeed;
	work2 		= (  work >> 1 ) ^ 0xff80;
	
	if ( (work & 0x1 ) == 0 ){
		if 		( work2 == 0xaa55 ) HiddenSeed = 0;
		else	HiddenSeed = work2 ^ 8180;
	} else {
		HiddenSeed = work2 ^ 0x8180;
	}

	return(HiddenSeed);

}


int GetRNG(int Limit)
{
    return((int)((float)(Random()/65535.0)*Limit));
}
