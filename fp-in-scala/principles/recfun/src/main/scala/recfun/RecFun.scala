package recfun

object RecFun extends RecFunInterface:

  def main(args: Array[String]): Unit =
    println("Pascal's Triangle")
    for row <- 0 to 10 do
      for col <- 0 to row do
        print(s"${pascal(col, row)} ")
      println()

  /**
   * Exercise 1
   */
  def pascal(c: Int, r: Int): Int =
    if (c < 0 || r < 0 || c > r)
      // This is probably not necessary for academic purposes, but it's here so that I can sleep smoothly.
      throw IllegalArgumentException()
    else
      // It could be improved using some memory structure (i.e dynamic programming using a map c,r -> pascal_result)
      // to avoid re-calculations, but this assignment is focus on recursion only, no need to complicate it
      if c == 0 || c == r then 1 else pascal(c, r - 1) + pascal(c - 1, r - 1)

  /**
   * Exercise 2
   */
  def balance(chars: List[Char]): Boolean =
    def balanceAux(chars: List[Char], balanceSum: Int): Boolean =
      if (chars.isEmpty)
        balanceSum == 0
      else if (balanceSum < 0)
        false
      else
        val currentCharWeigth: Int = chars.head match {
          case '(' => 1
          case ')' => -1
          case _ => 0
        }
        balanceAux(chars.tail, balanceSum + currentCharWeigth)

    balanceAux(chars, 0)

  /**
   * Exercise 3
   * Hints:
   * Think of the degenerate cases. How many ways can you give change for 0 CHF?
   * How many ways can you give change for >0 CHF, if you have no coins?
   */
  def countChange(money: Int, coins: List[Int]): Int =
    if (money == 0)
      1
    else if (money < 0 || coins.isEmpty)
      0
    else
      countChange(money - coins.head, coins) + countChange(money, coins.tail)
