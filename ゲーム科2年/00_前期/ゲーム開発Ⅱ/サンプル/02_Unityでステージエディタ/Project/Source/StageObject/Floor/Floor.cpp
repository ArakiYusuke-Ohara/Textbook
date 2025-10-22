#include "Floor.h"

#define DEFAULT_POS VGet(0.0f, 0.0f, 0.0f)

StageObject* Floor::Clone()
{
	Floor* clone = new Floor;

	*clone = *this;
	clone->m_Handle = MV1DuplicateModel(m_Handle);

	return clone;
}

