/*
 * Copyright (c) 2001-2004 MUSIC TECHNOLOGY GROUP (MTG)
 *                         UNIVERSITAT POMPEU FABRA
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include "XercesDomWriter.hxx"
#include "XercesEncodings.hxx"
#include "XercesInitializer.hxx"

#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/dom/DOMLSSerializer.hpp>
#include <xercesc/framework/MemBufFormatTarget.hpp>
#include <string>
#include <sstream>

#ifdef XERCES_CPP_NAMESPACE_USE
XERCES_CPP_NAMESPACE_USE
#endif

namespace CLAM
{
	void XercesDomWriter::write(std::ostream & target, xercesc::DOMNode * node)
	{
		xercesc::DOMLSSerializer* xercesWriter = NULL;
		xercesc::DOMLSOutput* theOutputDesc = NULL; //ouput destination
		xercesc::DOMConfiguration* dcfg = NULL; //configuration obj
		xercesc::XMLFormatTarget* memTarget = NULL; //to hold the bytestream		
		
		XMLCh tempStr[100];
		XMLString::transcode("LS", tempStr, 99);
		
		XercesInitializer::require();
		const XMLCh * propertyCanonical = xercesc::XMLUni::fgDOMWRTCanonicalForm;
		const XMLCh * propertyPrettyPrint = xercesc::XMLUni::fgDOMWRTFormatPrettyPrint;
		xercesc::DOMImplementation *impl = 
			xercesc::DOMImplementationRegistry::getDOMImplementation(tempStr);
		CHECKNULL(impl, L"MgXmlUtil.ToBytes");
		xercesWriter = ((DOMImplementationLS*)impl)->createLSSerializer();
		theOutputDesc = ((DOMImplementationLS*)impl)->createLSOutput();
		CHECKNULL(theSerializer, L"MgXmlUtil.ToBytes");
		CHECKNULL(theOutputDesc, L"MgXmlUtil.ToBytes");
    
		dcfg = xercesWriter->getDomConfig();
		
		if (dcfg->canSetParameter(propertyPrettyPrint, mShouldIndent))
			dcfg->setParameter(propertyPrettyPrint, mShouldIndent);
		if (dcfg->canSetParameter(propertyCanonical, mShouldCanonicalize))
			dcfg->setParameter(propertyCanonical, mShouldCanonicalize);

		// set user specified output encoding
		XMLCh encodeStr[100];
		XMLString::transcode("UTF-8", encodeStr, 99);
		theOutputDesc->setEncoding(encodeStr);
		
		xercesc::MemBufFormatTarget * xercesTarget = new xercesc::MemBufFormatTarget();
		xercesWriter->writeNode(xercesTarget, *node);
		const char * buffer = (char *) xercesTarget->getRawBuffer();
		const unsigned bufferLen = xercesTarget->getLen();
		target << std::string(buffer,bufferLen);
		delete xercesWriter;
		delete xercesTarget;
	}

}

