#ifndef EXRPC_ONEWAY_HPP
#define EXRPC_ONEWAY_HPP

#include <string>
#include <sstream>

#include "exrpc.hpp"
#include "exrpc_result.hpp"

namespace frovedis {

#define exrpc_oneway(n, f, ...) exrpc_function_oneway(n, #f, f, __VA_ARGS__)

#define exrpc_oneway0(n, f) exrpc_function_oneway(n, #f, f)

void send_exrpcreq_oneway(exrpc_node& n, const std::string&, const std::string&);

template <class T1, class T2, class T3, class T4, class T5, class T6,
          class T7, class T8, class T9, class T10, class T11>
void pfwrapper_oneway(intptr_t function_addr, my_portable_iarchive& inar)
{
  typedef void(*Ftype)(T1&,T2&,T3&,T4&,T5&,T6&,T7&,T8&,T9&,T10&,T11&);
  Ftype f = reinterpret_cast<Ftype>(function_addr);
  T1 a1;
  T2 a2;
  T3 a3;
  T4 a4;
  T5 a5;
  T6 a6;
  T7 a7;
  T8 a8;
  T9 a9;
  T10 a10;
  T11 a11;
  inar >> a1;
  inar >> a2;
  inar >> a3;
  inar >> a4;
  inar >> a5;
  inar >> a6;
  inar >> a7;
  inar >> a8;
  inar >> a9;
  inar >> a10;
  inar >> a11;
  f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11);
  return;
}

template <class T1, class T2, class T3, class T4, class T5, class T6,
          class T7, class T8, class T9, class T10>
void pfwrapper_oneway(intptr_t function_addr, my_portable_iarchive& inar)
{
  typedef void(*Ftype)(T1&,T2&,T3&,T4&,T5&,T6&,T7&,T8&,T9&,T10&);
  Ftype f = reinterpret_cast<Ftype>(function_addr);
  T1 a1;
  T2 a2;
  T3 a3;
  T4 a4;
  T5 a5;
  T6 a6;
  T7 a7;
  T8 a8;
  T9 a9;
  T10 a10;
  inar >> a1;
  inar >> a2;
  inar >> a3;
  inar >> a4;
  inar >> a5;
  inar >> a6;
  inar >> a7;
  inar >> a8;
  inar >> a9;
  inar >> a10;
  f(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10);
  return;
}

template <class T1, class T2, class T3, class T4, class T5, class T6,
          class T7, class T8, class T9>
void pfwrapper_oneway(intptr_t function_addr, my_portable_iarchive& inar)
{
  typedef void(*Ftype)(T1&,T2&,T3&,T4&,T5&,T6&,T7&,T8&,T9&);
  Ftype f = reinterpret_cast<Ftype>(function_addr);
  T1 a1;
  T2 a2;
  T3 a3;
  T4 a4;
  T5 a5;
  T6 a6;
  T7 a7;
  T8 a8;
  T9 a9;
  inar >> a1;
  inar >> a2;
  inar >> a3;
  inar >> a4;
  inar >> a5;
  inar >> a6;
  inar >> a7;
  inar >> a8;
  inar >> a9;
  f(a1,a2,a3,a4,a5,a6,a7,a8,a9);
  return;
}

template <class T1, class T2, class T3, class T4, class T5, class T6,
          class T7, class T8>
void pfwrapper_oneway(intptr_t function_addr, my_portable_iarchive& inar)
{
  typedef void(*Ftype)(T1&,T2&,T3&,T4&,T5&,T6&,T7&,T8&);
  Ftype f = reinterpret_cast<Ftype>(function_addr);
  T1 a1;
  T2 a2;
  T3 a3;
  T4 a4;
  T5 a5;
  T6 a6;
  T7 a7;
  T8 a8;
  inar >> a1;
  inar >> a2;
  inar >> a3;
  inar >> a4;
  inar >> a5;
  inar >> a6;
  inar >> a7;
  inar >> a8;
  f(a1,a2,a3,a4,a5,a6,a7,a8);
  return;
}

template <class T1, class T2, class T3, class T4, class T5, class T6, class T7>
void pfwrapper_oneway(intptr_t function_addr, my_portable_iarchive& inar)
{
  typedef void(*Ftype)(T1&,T2&,T3&,T4&,T5&,T6&,T7&);
  Ftype f = reinterpret_cast<Ftype>(function_addr);
  T1 a1;
  T2 a2;
  T3 a3;
  T4 a4;
  T5 a5;
  T6 a6;
  T7 a7;
  inar >> a1;
  inar >> a2;
  inar >> a3;
  inar >> a4;
  inar >> a5;
  inar >> a6;
  inar >> a7;
  f(a1,a2,a3,a4,a5,a6,a7);
  return;
}

template <class T1, class T2, class T3, class T4, class T5, class T6>
void pfwrapper_oneway(intptr_t function_addr, my_portable_iarchive& inar)
{
  typedef void(*Ftype)(T1&,T2&,T3&,T4&,T5&,T6&);
  Ftype f = reinterpret_cast<Ftype>(function_addr);
  T1 a1;
  T2 a2;
  T3 a3;
  T4 a4;
  T5 a5;
  T6 a6;
  inar >> a1;
  inar >> a2;
  inar >> a3;
  inar >> a4;
  inar >> a5;
  inar >> a6;
  f(a1,a2,a3,a4,a5,a6);
  return;
}

template <class T1, class T2, class T3, class T4, class T5>
void pfwrapper_oneway(intptr_t function_addr, my_portable_iarchive& inar)
{
  typedef void(*Ftype)(T1&,T2&,T3&,T4&,T5&);
  Ftype f = reinterpret_cast<Ftype>(function_addr);
  T1 a1;
  T2 a2;
  T3 a3;
  T4 a4;
  T5 a5;
  inar >> a1;
  inar >> a2;
  inar >> a3;
  inar >> a4;
  inar >> a5;
  f(a1,a2,a3,a4,a5);
  return;
}

template <class T1, class T2, class T3, class T4>
void pfwrapper_oneway(intptr_t function_addr, my_portable_iarchive& inar)
{
  typedef void(*Ftype)(T1&,T2&,T3&,T4&);
  Ftype f = reinterpret_cast<Ftype>(function_addr);
  T1 a1;
  T2 a2;
  T3 a3;
  T4 a4;
  inar >> a1;
  inar >> a2;
  inar >> a3;
  inar >> a4;
  f(a1,a2,a3,a4);
  return;
}

template <class T1, class T2, class T3>
void pfwrapper_oneway(intptr_t function_addr, my_portable_iarchive& inar)
{
  typedef void(*Ftype)(T1&,T2&,T3&);
  Ftype f = reinterpret_cast<Ftype>(function_addr);
  T1 a1;
  T2 a2;
  T3 a3;
  inar >> a1;
  inar >> a2;
  inar >> a3;
  f(a1,a2,a3);
  return;
}

template <class T1, class T2>
void pfwrapper_oneway(intptr_t function_addr, my_portable_iarchive& inar)
{
  typedef void(*Ftype)(T1&,T2&);
  Ftype f = reinterpret_cast<Ftype>(function_addr);
  T1 a1;
  T2 a2;
  inar >> a1;
  inar >> a2;
  f(a1,a2);
  return;
}

template <class T1>
void pfwrapper_oneway(intptr_t function_addr, my_portable_iarchive& inar) {
  typedef void(*Ftype)(T1&);
  Ftype f = reinterpret_cast<Ftype>(function_addr);
  T1 a1;
  inar >> a1;
  f(a1);
  return;
}

template <class T1, class T2, class T3, class T4, class T5,
          class T6, class T7, class T8, class T9, class T10, class T11>
void exrpc_function_oneway(exrpc_node& n, std::string fn,
                           void(*f)(T1&,T2&,T3&,T4&,T5&,T6&,T7&,T8&,T9&,T10&,T11&),
                           const T1& a1, const T2& a2, const T3& a3,
                           const T4& a4, const T5& a5, const T6& a6,
                           const T7& a7, const T8& a8, const T9& a9,
                           const T10& a10, const T11& a11) {
  std::ostringstream outss;
  my_portable_oarchive outar(outss);
  outar << a1;
  outar << a2;
  outar << a3;
  outar << a4;
  outar << a5;
  outar << a6;
  outar << a7;
  outar << a8;
  outar << a9;
  outar << a10;
  outar << a11;
  send_exrpcreq_oneway(n, fn, outss.str());
}

template <class T1, class T2, class T3, class T4, class T5, 
          class T6, class T7, class T8, class T9, class T10>
void exrpc_function_oneway(exrpc_node& n, std::string fn,
                           void(*f)(T1&,T2&,T3&,T4&,T5&,T6&,T7&,T8&,T9&,T10&),
                           const T1& a1, const T2& a2, const T3& a3,
                           const T4& a4, const T5& a5, const T6& a6,
                           const T7& a7, const T8& a8, const T9& a9,
                           const T10& a10) {
  std::ostringstream outss;
  my_portable_oarchive outar(outss);
  outar << a1;
  outar << a2;
  outar << a3;
  outar << a4;
  outar << a5;
  outar << a6;
  outar << a7;
  outar << a8;
  outar << a9;
  outar << a10;
  send_exrpcreq_oneway(n, fn, outss.str());
}

template <class T1, class T2, class T3, class T4, class T5,
          class T6, class T7, class T8, class T9>
void exrpc_function_oneway(exrpc_node& n, std::string fn,
                           void(*f)(T1&,T2&,T3&,T4&,T5&,T6&,T7&,T8&,T9&),
                           const T1& a1, const T2& a2, const T3& a3,
                           const T4& a4, const T5& a5, const T6& a6,
                           const T7& a7, const T8& a8, const T9& a9) {
  std::ostringstream outss;
  my_portable_oarchive outar(outss);
  outar << a1;
  outar << a2;
  outar << a3;
  outar << a4;
  outar << a5;
  outar << a6;
  outar << a7;
  outar << a8;
  outar << a9;
  send_exrpcreq_oneway(n, fn, outss.str());
}

template <class T1, class T2, class T3, class T4, class T5, 
          class T6, class T7, class T8>
void exrpc_function_oneway(exrpc_node& n, std::string fn,
                           void(*f)(T1&,T2&,T3&,T4&,T5&,T6&,T7&,T8&),
                           const T1& a1, const T2& a2, const T3& a3,
                           const T4& a4, const T5& a5, const T6& a6,
                           const T7& a7, const T8& a8) {
  std::ostringstream outss;
  my_portable_oarchive outar(outss);
  outar << a1;
  outar << a2;
  outar << a3;
  outar << a4;
  outar << a5;
  outar << a6;
  outar << a7;
  outar << a8;
  send_exrpcreq_oneway(n, fn, outss.str());
}

template <class T1, class T2, class T3, class T4, class T5,
          class T6, class T7>
void exrpc_function_oneway(exrpc_node& n, std::string fn,
                           void(*f)(T1&,T2&,T3&,T4&,T5&,T6&,T7&),
                           const T1& a1, const T2& a2, const T3& a3,
                           const T4& a4, const T5& a5, const T6& a6,
                           const T7& a7) {
  std::ostringstream outss;
  my_portable_oarchive outar(outss);
  outar << a1;
  outar << a2;
  outar << a3;
  outar << a4;
  outar << a5;
  outar << a6;
  outar << a7;
  send_exrpcreq_oneway(n, fn, outss.str());
}

template <class T1, class T2, class T3, class T4, class T5,
          class T6>
void exrpc_function_oneway(exrpc_node& n, std::string fn,
                           void(*f)(T1&,T2&,T3&,T4&,T5&,T6&),
                           const T1& a1, const T2& a2, const T3& a3,
                           const T4& a4, const T5& a5, const T6& a6) {
  std::ostringstream outss;
  my_portable_oarchive outar(outss);
  outar << a1;
  outar << a2;
  outar << a3;
  outar << a4;
  outar << a5;
  outar << a6;
  send_exrpcreq_oneway(n, fn, outss.str());
}

template <class T1, class T2, class T3, class T4, class T5>
void exrpc_function_oneway(exrpc_node& n, std::string fn,
                           void(*f)(T1&,T2&,T3&,T4&,T5&),
                           const T1& a1, const T2& a2, const T3& a3,
                           const T4& a4, const T5& a5) {
  std::ostringstream outss;
  my_portable_oarchive outar(outss);
  outar << a1;
  outar << a2;
  outar << a3;
  outar << a4;
  outar << a5;
  send_exrpcreq_oneway(n, fn, outss.str());
}

template <class T1, class T2, class T3, class T4>
void exrpc_function_oneway(exrpc_node& n, std::string fn,
                           void(*f)(T1&,T2&,T3&,T4&),
                           const T1& a1, const T2& a2, const T3& a3,
                           const T4& a4) {
  std::ostringstream outss;
  my_portable_oarchive outar(outss);
  outar << a1;
  outar << a2;
  outar << a3;
  outar << a4;
  send_exrpcreq_oneway(n, fn, outss.str());
}

template <class T1, class T2, class T3>
void exrpc_function_oneway(exrpc_node& n, std::string fn,
                           void(*f)(T1&,T2&,T3&),
                           const T1& a1, const T2& a2, const T3& a3) {
  std::ostringstream outss;
  my_portable_oarchive outar(outss);
  outar << a1;
  outar << a2;
  outar << a3;
  send_exrpcreq_oneway(n, fn, outss.str());
}

template <class T1, class T2>
void exrpc_function_oneway(exrpc_node& n, std::string fn,
                           void(*f)(T1&,T2&),
                           const T1& a1, const T2& a2) {
  std::ostringstream outss;
  my_portable_oarchive outar(outss);
  outar << a1;
  outar << a2;
  send_exrpcreq_oneway(n, fn, outss.str());
}

template <class T1>
void exrpc_function_oneway(exrpc_node& n, std::string fn,
                           void(*f)(T1&),
                           const T1& a1) {
  std::ostringstream outss;
  my_portable_oarchive outar(outss);
  outar << a1;
  send_exrpcreq_oneway(n, fn, outss.str());
}

void exrpc_function_oneway(exrpc_node& n, std::string fn, void(*f)());

}

#endif
