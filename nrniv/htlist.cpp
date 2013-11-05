#include <nrnconf.h>
/*
Based on Unidraw UList but UList changed to HTList (head tail list)
for fast insertion, deletion, iteration
*/

/*
 * Copyright (c) 1990, 1991 Stanford University
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Stanford not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  Stanford makes no representations about
 * the suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 * STANFORD DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
 * IN NO EVENT SHALL STANFORD BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * HTList implementation.
 */

#include <htlist.h>

/*****************************************************************************/

HTList::HTList (void* p) { _next = this; _prev = this; _object = p; }

HTList::~HTList () {
    HTList* next = _next;
    if (next != this && next != nil) {
        Remove(this);
        delete next;
    }
}

void HTList::Append (HTList* e) {
    _prev->_next = e;
    e->_prev = _prev;
    e->_next = this;
    _prev = e;
}

void HTList::Prepend (HTList* e) {
    _next->_prev = e;
    e->_prev = this;
    e->_next = _next;
    _next = e;
}

void HTList::Remove (HTList* e) {
    e->_prev->_next = e->_next;
    e->_next->_prev = e->_prev;
    e->_prev = e->_next = nil;
}

void HTList::Remove() {
	if (_prev) { _prev->_next = _next; }
	if (_next) { _next->_prev = _prev; }
	_prev = _next = nil;
}
void HTList::RemoveAll() {
	while(!IsEmpty()) {
		Remove(First());
	}
}
void HTList::Delete (void* p) {
    register HTList* e;

    e = Find(p);
    if (e != nil) {
	Remove(e);
	delete e;
    }
}

HTList* HTList::Find (void* p) {
    register HTList* e;

    for (e = _next; e != this; e = e->_next) {
	if (e->_object == p) {
	    return e;
	}
    }
    return nil;
}

HTList* HTList::operator[] (int count) {
    HTList* pos = First();
    int i;

    for (i = 1; i < count && pos != End(); ++i) {
	pos = pos->Next();
    }
    if (i == count) {
	return pos;
    }
    return nil;
}	