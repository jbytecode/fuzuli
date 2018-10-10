/*
** socket.hxx
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Tue Jun  1 22:45:16 2004 Julien Lemoine
** $Id: socket.hxx,v 1.2 2004/11/14 19:37:46 speedblue Exp $
** 
** Copyright (C) 2004 Julien Lemoine
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

#ifndef   	SOCKET_HXX_
# define   	SOCKET_HXX_

namespace Network
{
  inline bool Socket::_check_answer(int res, std::string &str)
  {
    if (res <= 0)
      {
	if (!_buffer.size()) // No more data...
	  throw ConnectionClosed("Connection Closed", HERE);
	else
	  {
	    str += _buffer;
	    _buffer = "";
	    _state_timeout = 0;
	    return true;
	  }
      }
    return false;
  }

  inline bool Socket::_update_buffer(std::pair<int, int> &delim,
				     int &i, std::string &str)
  {
    delim = _find_delim(_buffer, 0);
    i = delim.first;
    while (!_empty_lines && !i)
      {
	// remove delimiter in front of buffer
	_buffer = _buffer.substr(delim.second, _buffer.size() - delim.second);
	delim = _find_delim(_buffer, 0);
	i = delim.first;
      }
    if ((i > 0 || _empty_lines) && ((unsigned int)i < _buffer.size()))
      {
	str = _buffer.substr(0, i);
	_buffer = _buffer.substr(i + delim.second, 
				 _buffer.size() - i - delim.second);
	return true;
      }
    else 
      return false;
  }
}

#endif	    /* !SOCKET_HXX_ */
