// Benchmark "CSAMultiplier" written by ABC on Tue Jul 19 13:59:16 2016

module CSAMultiplier ( 
    a0, a1, a2, a3, b0, b1, b2, b3,
    z0, z1, z2, z3, z4, z5, z6, z7  );
  input  a0, a1, a2, a3, b0, b1, b2, b3;
  output z0, z1, z2, z3, z4, z5, z6, z7;
  wire n18, n19, n21, n22, n23, n24, n25, n26, n27, n28, n30, n31, n32, n33,
    n34, n35, n36, n37, n38, n39, n40, n41, n42, n44, n45, n46, n47, n48,
    n49, n50, n51, n52, n53, n54, n55, n56, n57, n58, n60, n61, n62, n63,
    n64, n65, n66, n67, n68, n69, n70, n71, n72, n73, n74, n75, n76, n78,
    n79, n80, n81, n82, n83, n84, n85, n86, n88, n89;
  and2  g00(.a(b0), .b(a0), .O(z0));
  nand2 g01(.a(b1), .b(a0), .O(n18));
  nand2 g02(.a(b0), .b(a1), .O(n19));
  xor2  g03(.a(n19), .b(n18), .O(z1));
  inv1  g04(.a(a0), .O(n21));
  inv1  g05(.a(b2), .O(n22));
  nor2  g06(.a(n22), .b(n21), .O(n23));
  nor2  g07(.a(n19), .b(n18), .O(n24));
  xor2  g08(.a(n24), .b(n23), .O(n25));
  nand2 g09(.a(b1), .b(a1), .O(n26));
  nand2 g10(.a(b0), .b(a2), .O(n27));
  xor2  g11(.a(n27), .b(n26), .O(n28));
  xor2  g12(.a(n28), .b(n25), .O(z2));
  inv1  g13(.a(b3), .O(n30));
  nor2  g14(.a(n30), .b(n21), .O(n31));
  nand2 g15(.a(n28), .b(n24), .O(n32));
  oai21 g16(.a(n28), .b(n24), .c(n23), .O(n33));
  nand2 g17(.a(n33), .b(n32), .O(n34));
  xor2  g18(.a(n34), .b(n31), .O(n35));
  and2  g19(.a(b2), .b(a1), .O(n36));
  nand2 g20(.a(b1), .b(a2), .O(n37));
  nand2 g21(.a(b0), .b(a3), .O(n38));
  xor2  g22(.a(n38), .b(n37), .O(n39));
  xor2  g23(.a(n39), .b(n36), .O(n40));
  nor2  g24(.a(n27), .b(n26), .O(n41));
  xor2  g25(.a(n41), .b(n40), .O(n42));
  xor2  g26(.a(n42), .b(n35), .O(z3));
  nand2 g27(.a(b3), .b(a1), .O(n44));
  nand2 g28(.a(b2), .b(a2), .O(n45));
  nand2 g29(.a(b1), .b(a3), .O(n46));
  xor2  g30(.a(n46), .b(n45), .O(n47));
  nor2  g31(.a(n38), .b(n37), .O(n48));
  xor2  g32(.a(n48), .b(n47), .O(n49));
  xor2  g33(.a(n49), .b(n44), .O(n50));
  nand2 g34(.a(n41), .b(n39), .O(n51));
  oai21 g35(.a(n41), .b(n39), .c(n36), .O(n52));
  nand2 g36(.a(n52), .b(n51), .O(n53));
  xor2  g37(.a(n53), .b(n50), .O(n54));
  inv1  g38(.a(n54), .O(n55));
  nand2 g39(.a(n42), .b(n34), .O(n56));
  oai21 g40(.a(n42), .b(n34), .c(n31), .O(n57));
  nand2 g41(.a(n57), .b(n56), .O(n58));
  xor2  g42(.a(n58), .b(n55), .O(z4));
  aoi21 g43(.a(n57), .b(n56), .c(n54), .O(n60));
  nand2 g44(.a(b3), .b(a2), .O(n61));
  inv1  g45(.a(a3), .O(n62));
  nor2  g46(.a(n22), .b(n62), .O(n63));
  xor2  g47(.a(n63), .b(n61), .O(n64));
  inv1  g48(.a(n64), .O(n65));
  inv1  g49(.a(n46), .O(n66));
  nand2 g50(.a(n48), .b(n66), .O(n67));
  inv1  g51(.a(n45), .O(n68));
  oai21 g52(.a(n48), .b(n66), .c(n68), .O(n69));
  nand2 g53(.a(n69), .b(n67), .O(n70));
  xor2  g54(.a(n70), .b(n65), .O(n71));
  xor2  g55(.a(n71), .b(n60), .O(n72));
  nand2 g56(.a(n53), .b(n49), .O(n73));
  inv1  g57(.a(n44), .O(n74));
  oai21 g58(.a(n53), .b(n49), .c(n74), .O(n75));
  nand2 g59(.a(n75), .b(n73), .O(n76));
  xor2  g60(.a(n76), .b(n72), .O(z5));
  nand2 g61(.a(n76), .b(n60), .O(n78));
  oai21 g62(.a(n76), .b(n60), .c(n71), .O(n79));
  nand2 g63(.a(n79), .b(n78), .O(n80));
  nor2  g64(.a(n30), .b(n62), .O(n81));
  xor2  g65(.a(n81), .b(n80), .O(n82));
  nand2 g66(.a(n70), .b(n63), .O(n83));
  inv1  g67(.a(n61), .O(n84));
  oai21 g68(.a(n70), .b(n63), .c(n84), .O(n85));
  nand2 g69(.a(n85), .b(n83), .O(n86));
  xor2  g70(.a(n86), .b(n82), .O(z6));
  nand2 g71(.a(n86), .b(n80), .O(n88));
  oai21 g72(.a(n86), .b(n80), .c(n81), .O(n89));
  nand2 g73(.a(n89), .b(n88), .O(z7));
endmodule


