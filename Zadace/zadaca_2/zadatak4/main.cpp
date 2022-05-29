int main() {
  Polinom p1({-1,2});   // P(x): -1 + 2*x
  Polinom p2(3);        // polinom drugog stepena (a + b*x + c*x^2)
  std::cin >> p2;       // učitati sa tastature polinom drugog stepena 

  std::cout << "P1(x): " << p1 << std::endl;
  std::cout << "P2(x): " << p2 << std::endl;

  auto p3 = p1 + p2;
  auto p4 = p2 - p1;
  auto p5 = p1 * p2;

  std::cout << "P3(x): " << p3 << std::endl;
  std::cout << "P4(x): " << p4 << std::endl;
  std::cout << "P5(x): " << p5 << std::endl;

  double rezultat = p3(5);
  std::cout << "P3(5): " << rezultat << std::endl;

  p3 = p2.izvod();
  std::cout << "P2'(x): " << p3 << std::endl;

  std::cout << "P2'(5): " << p3(5) << std::endl;

  p2 += p1;
}
