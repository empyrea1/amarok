// FHT - Fast Hartley Transform Class
//
// Copyright (C) 2004  Melchior FRANZ - mfranz@kde.org
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
//
// $Id$

class FHT {
	int		m_exp2;
	int		m_num;
	double		*m_buf;
	double		*m_tab;

	void		makeCasTable();

public:
	FHT(int);
	~FHT();
	inline int	sizeExp() const { return m_exp2; }
	inline int	size() const { return m_num; }
	void 		__transform(double *, int, int);
	inline void	transform8(double *);
	void		transform(double *);
	inline double	_transform(double *);
	void		power(double *);
	double		_power(double *);
	double		*copy(double *, double *);
	double		*clear(double *);
	inline void	scale(double *, double);
};


