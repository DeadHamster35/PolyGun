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


float tandy(float Input) {
    float sin_val;
    float cos_val;
    float tan_val;

    // Calculate sine and cosine
    sin_val = (float)(sint(Input) / DEG1);
    cos_val = (float)(cost(Input) / DEG1);

    // Compute the tangent using the quotient identity
    if (cos_val != 0) {
        tan_val = sin_val / cos_val;
    } else {
        tan_val = 0.0f; // Assign a very large value to indicate overflow
    }
    return tan_val;
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


ushort atan3(float y, float x)
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



typedef union {
	long	word;
	short	half[2];
	char	byte[4];	
} SPacked;
void AffineToMtx(AffineMtx Affine, Mtx *Matrix)
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





// Zero + identity
static void Mtx_Identity(AffineMtx m) {
    // zero everything
    for (int r = 0; r < 4; ++r)
        for (int c = 0; c < 4; ++c)
            m[r][c] = 0.0f;

    // set diagonal to 1
    m[0][0] = 1.0f;
    m[1][1] = 1.0f;
    m[2][2] = 1.0f;
    m[3][3] = 1.0f;
}

// Rotate around Z: affects X,Y columns
static void Mtx_RotateZ(AffineMtx m, short ang) {
    float s = sint(ang);
    float c = cost(ang);

    for (int row = 0; row < 4; ++row) {
        float x = m[row][0];
        float y = m[row][1];
        m[row][0] = x * c - y * s;
        m[row][1] = x * s + y * c;
    }
}

// Rotate around Y: affects X,Z columns
static void Mtx_RotateY(AffineMtx m, short ang) {
    float s = sint(ang);
    float c = cost(ang);

    for (int row = 0; row < 4; ++row) {
        float x = m[row][0];
        float z = m[row][2];
        m[row][0] =  x * c + z * s;
        m[row][2] = -x * s + z * c;
    }
}

// Rotate around X: affects Y,Z columns
static void Mtx_RotateX(AffineMtx m, short ang) {
    float s = sint(ang);
    float c = cost(ang);

    for (int row = 0; row < 4; ++row) {
        float y = m[row][1];
        float z = m[row][2];
        m[row][1] = y * c - z * s;
        m[row][2] = y * s + z * c;
    }
}


void CreateModelMatrix(AffineMtx dst,Vector pos, SVector ang)
{
    Mtx_Identity(dst);
    
    Mtx_RotateX(dst, ang[0]);
    
    if (ang[1] != 0)
    {
        Mtx_RotateY(dst, ang[1]);
    }
    
    Mtx_RotateZ(dst, ang[2]);

    dst[3][0] = pos[0];
    dst[3][1] = pos[1];
    dst[3][2] = pos[2];

}

void CreatePositionMatrix(AffineMtx dst, Vector pos)
{
    Mtx_Identity(dst);
    dst[3][0] = pos[0];
    dst[3][1] = pos[1];
    dst[3][2] = pos[2];
}


void MatrixMultiply(AffineMtx out, AffineMtx a, AffineMtx b)
{
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            out[row][col] = 
                a[row][0] * b[0][col] +
                a[row][1] * b[1][col] +
                a[row][2] * b[2][col] +
                a[row][3] * b[3][col];
        }
    }
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
    Matrix[0][0] *= (float)(FScale[0] * 0.01f);
    Matrix[1][0] *= (float)(FScale[0] * 0.01f);
    Matrix[2][0] *= (float)(FScale[0] * 0.01f);
    Matrix[1][0] *= (float)(FScale[1] * 0.01f);
    Matrix[1][1] *= (float)(FScale[1] * 0.01f);
    Matrix[1][2] *= (float)(FScale[1] * 0.01f);
    Matrix[2][0] *= (float)(FScale[2] * 0.01f);
    Matrix[2][1] *= (float)(FScale[2] * 0.01f);
    Matrix[2][2] *= (float)(FScale[2] * 0.01f);
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
    return (-1 * atan3((B[0] - A[0]),(B[1] - A[1])));
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
