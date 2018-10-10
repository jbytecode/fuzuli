/*
** socketexception.cc
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Mon May 12 23:23:27 2003 Julien Lemoine
** $Id: socketexception.cc,v 1.2 2004/06/01 21:30:53 speedblue Exp $
** 
** Copyright (C) 2003,2004 Julien Lemoine
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
** 
** You should have received a copy of the GNU Lesser General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include "socketexception.hh"

namespace Network
{
  std::ostream& operator<<(std::ostream& stream, Exception& e)
  {
    e.print(stream);
    return (stream);
  }


  const std::string& Exception::get_error() const
  {
    return _error;
  }

  const char* Exception::get_file() const
  {
    return _file;
  }

  int Exception::get_line() const
  {
    return _line;
  }

  void Exception::print(std::ostream& stream) const
  {
    if (_file)
      stream << _error << " [" << _file << ":" << _line << "]"<<std::endl;
    else
      stream << _error << std::endl;
  }

}
