package funsets

/**
 * This class is a test suite for the methods in object FunSets.
 *
 * To run this test suite, start "sbt" then run the "test" command.
 */
class FunSetSuite extends munit.FunSuite:

  import FunSets.*

  test("contains is implemented") {
    assert(contains(x => true, 100))
  }

  /**
   * When writing tests, one would often like to re-use certain values for multiple
   * tests. For instance, we would like to create an Int-set and have multiple test
   * about it.
   *
   * Instead of copy-pasting the code for creating the set into every test, we can
   * store it in the test class using a val:
   *
   *   val s1 = singletonSet(1)
   *
   * However, what happens if the method "singletonSet" has a bug and crashes? Then
   * the test methods are not even executed, because creating an instance of the
   * test class fails!
   *
   * Therefore, we put the shared values into a separate trait (traits are like
   * abstract classes), and create an instance inside each test method.
   *
   */

  trait TestSets:
    val s1 = singletonSet(1)
    val s2 = singletonSet(2)
    val s3 = singletonSet(3)
    val evenNumSet: FunSet = x => x % 2 == 0
    val negativeNumSet: FunSet = x => x < 0

  /**
   * This test is currently disabled (by using @Ignore) because the method
   * "singletonSet" is not yet implemented and the test would fail.
   *
   * Once you finish your implementation of "singletonSet", remove the
   * .ignore annotation.
   */
  test("singleton set one contains one") {

    /**
     * We create a new instance of the "TestSets" trait, this gives us access
     * to the values "s1" to "s3".
     */
    new TestSets:
      /**
       * The string argument of "assert" is a message that is printed in case
       * the test fails. This helps identifying which assertion failed.
       */
      assert(contains(s1, 1), "Singleton")
  }

  test("union contains all elements of each set") {
    new TestSets:
      val s = union(s1, s2)
      assert(contains(s, 1), "Union 1")
      assert(contains(s, 2), "Union 2")
      assert(!contains(s, 3), "Union 3")
  }

  test("intersect contains common elements from both sets") {
    new TestSets:
      val interSet1 = intersect(singletonSet(-1), negativeNumSet)
      assert(contains(interSet1, -1), "intersect -1")
      assert(!contains(interSet1, -2), "intersect -2")
  }

  test("intersect is empty if no common elements from both sets") {
    new TestSets:
      val interSet1 = intersect(singletonSet(0), negativeNumSet)
      assert(!contains(interSet1, -1), "intersect -1")
      assert(!contains(interSet1, 0), "intersect 0")
      assert(!contains(interSet1, 1), "intersect 1")
  }

  test("filter selects only the elements for which the predicate is true") {
    new TestSets:
      val evenNumsGreaterThanMinusFour = filter(evenNumSet, x => x > -4)
      assert(!contains(evenNumsGreaterThanMinusFour, -4), "intersect -4")
      assert(contains(evenNumsGreaterThanMinusFour, -2), "intersect -2")
      assert(!contains(evenNumsGreaterThanMinusFour, 1), "intersect 1")
      assert(contains(evenNumsGreaterThanMinusFour, 2), "intersect 2")
  }

  test("forall tests whether a given predicate is true for all elements of the set") {
    new TestSets:
      val evenNumsGreaterThanMinusFour = filter(evenNumSet, x => x > -4)
      assert(forall(evenNumsGreaterThanMinusFour, x => x % 2 == 0), "forall x % 2 == 0")
      assert(forall(evenNumsGreaterThanMinusFour, x => x > -4), "forall x > -4")
      assert(!forall(evenNumsGreaterThanMinusFour, x => x == 0), "forall x = 0")
  }

  test("map tests whether a given predicate is true for all elements of the set") {
    val numArray = Array(1, 3, 4, 5, 7, 1000)
    val numSet: FunSet = x => numArray.contains(x)
    assertEquals(FunSets.toString(numSet), "{1,3,4,5,7,1000}")
    val newSet = map(numSet, x => x - 1)
    assertEquals(FunSets.toString(map(numSet, x => x - 1)), "{0,2,3,4,6,999}")
  }

  // Today is too sunny to write more tests

  import scala.concurrent.duration.*
  override val munitTimeout = 10.seconds
