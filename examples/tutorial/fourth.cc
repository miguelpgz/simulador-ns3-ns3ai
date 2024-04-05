/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ns3/object.h"
#include "ns3/uinteger.h"
#include "ns3/traced-value.h"
#include "ns3/trace-source-accessor.h"
#include "ns3/simulator.h"

#include <iostream>

using namespace ns3;

/**
 * Tutorial 4 - a simple Object to show how to hook a trace.
 */
class MyObject : public Object
{
public:
  /**
   * Register this type.
   * \return The TypeId.
   */
  static TypeId GetTypeId (void)
  {
    static TypeId tid = TypeId ("MyObject")
      .SetParent<Object> ()
      .SetGroupName ("Tutorial")
      .AddConstructor<MyObject> ()
      .AddTraceSource ("MyInteger",
                       "An integer value to trace.",
                       MakeTraceSourceAccessor (&MyObject::m_myInt),
                       "ns3::TracedValueCallback::Int32")
    ;
    return tid;
  }

  MyObject () {}
  TracedValue<int32_t> m_myInt; //!< The traced value.
};

void
IntTrace (int32_t oldValue, int32_t newValue)
{
  std::cout << "Traced " << oldValue << " to " << newValue << std::endl;
}
/*
En la funcion main, se crea una instancia de MyObject llamada myObject.
Se conecta la funcion IntTrace a la fuente de trazas "MyInteger" de myObject. Esto significa que cada vez que el valor de m_myInt cambie, se llamará a la función IntTrace.
Finalmente, se establece el valor de m_myInt en 1234, lo que provocará que se llame a la función IntTrace y se imprima el mensaje con el valor anterior (por defecto 0) y el nuevo valor (1234).
*/
int
main (int argc, char *argv[])
{
  Ptr<MyObject> myObject = CreateObject<MyObject> ();
  myObject->TraceConnectWithoutContext ("MyInteger", MakeCallback (&IntTrace));

  myObject->m_myInt = 4567;
  myObject->m_myInt = 4567;
}
