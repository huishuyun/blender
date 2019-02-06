/*
 * Copyright 2011, Blender Foundation.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "COM_GammaOperation.h"
#include "BLI_math.h"

GammaOperation::GammaOperation() : NodeOperation()
{
	this->addInputSocket(COM_DT_COLOR);
	this->addInputSocket(COM_DT_VALUE);
	this->addOutputSocket(COM_DT_COLOR);
	this->m_inputProgram = NULL;
	this->m_inputGammaProgram = NULL;
}
void GammaOperation::initExecution()
{
	this->m_inputProgram = this->getInputSocketReader(0);
	this->m_inputGammaProgram = this->getInputSocketReader(1);
}

void GammaOperation::executePixelSampled(float output[4], float x, float y, PixelSampler sampler)
{
	float inputValue[4];
	float inputGamma[4];

	this->m_inputProgram->readSampled(inputValue, x, y, sampler);
	this->m_inputGammaProgram->readSampled(inputGamma, x, y, sampler);
	const float gamma = inputGamma[0];
	/* check for negative to avoid nan's */
	output[0] = inputValue[0] > 0.0f ? powf(inputValue[0], gamma) : inputValue[0];
	output[1] = inputValue[1] > 0.0f ? powf(inputValue[1], gamma) : inputValue[1];
	output[2] = inputValue[2] > 0.0f ? powf(inputValue[2], gamma) : inputValue[2];

	output[3] = inputValue[3];
}

void GammaOperation::deinitExecution()
{
	this->m_inputProgram = NULL;
	this->m_inputGammaProgram = NULL;
}
