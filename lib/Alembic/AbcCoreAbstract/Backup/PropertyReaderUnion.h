//-*****************************************************************************
//
// Copyright (c) 2009-2010,
//  Sony Pictures Imageworks, Inc. and
//  Industrial Light & Magic, a division of Lucasfilm Entertainment Company Ltd.
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
// *       Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
// *       Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
// *       Neither the name of Sony Pictures Imageworks, nor
// Industrial Light & Magic nor the names of their contributors may be used
// to endorse or promote products derived from this software without specific
// prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//-*****************************************************************************

#ifndef _Alembic_AbcCoreAbstract_PropertyReaderUnion_h_
#define _Alembic_AbcCoreAbstract_PropertyReaderUnion_h_



namespace Alembic {
namespace AbcCoreAbstract {
namespace V0001 {

//-*****************************************************************************
class PropertyReaderUnion : private boost::noncopyable
{
public:
    virtual ~PropertyReaderUnion() {}
    virtual PropertyType getPropertyType() const = 0;
    virtual bool isScalar() const { return false; }
    virtual bool isArray() const { return false; }
    virtual bool isCompound() const { return false; }
    virtual const std::string &getName() const = 0;
    virtual const MetaData &getMetaData() const = 0;
    virtual ScalarPropertyReaderPtr getScalar() const
    { return ScalarPropertyReaderPtr(); }
    virtual ArrayPropertyReaderPtr getArray() const
    { return ArrayPropertyReaderPtr(); }
    virtual CompoundPropertyReaderPtr getCompound() const
    { return CompoundPropertyReaderPtr(); }
};

} // End namespace V0001
} // End namespace AbcCoreAbstract
} // End namespace Alembic

#endif