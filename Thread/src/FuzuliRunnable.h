/*
 * fuzuli : A general purpose interpreter
 * Copyright (C) 2012 Mehmet Hakan Satman <mhsatman@yahoo.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FUZULIRUNNABLE_H_
#define FUZULIRUNNABLE_H_

#include <FuzuliTypes.h>
#include <boost/thread.hpp>

namespace fuzuli {


class FuzuliRunnable {
public:
	FuzuliRunnable();
	virtual ~FuzuliRunnable();
	FunctionCallExpression *fcallexpr;
	FuzuliFunction *func;
	boost::thread *t;
	Environment *env;
	void CreateThread(const char *fname, Environment *env);
	void run();
};

}
#endif /* FUZULIRUNNABLE_H_ */
