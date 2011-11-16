import org.junit.*;

import static org.junit.Assert.*;

public class TestBinaryCode {
    BinaryCode code;

    @Before
    public void setUp() {
        code = new BinaryCode();
    }

    @Test
    public void test0() {
        String[] res = code.decode("123210122");
        assertEquals("011100011", res[0]);
        assertEquals("NONE", res[1]);
    }

    @Test
    public void test1() {
        String[] res = code.decode("11");
        assertEquals("01", res[0]);
        assertEquals("10", res[1]);
    }

    @Test
    public void test2() {
        String[] res = code.decode("22111");
        assertEquals("NONE", res[0]);
        assertEquals("11001", res[1]);
    }

    @Test
    public void test3() {
        String[] res = code.decode("123210120");
        assertEquals("First", "NONE", res[0]);
        assertEquals("Second", "NONE", res[1]);
    }

    @Test
    public void test4() {
        String[] res = code.decode("3");
        assertEquals("First", "NONE", res[0]);
        assertEquals("Second", "NONE", res[1]);
    }

    @Test
    public void test5() {
        String[] res = code.decode("12221112222221112221111111112221111");
        assertEquals("01101001101101001101001001001101001", res[0]);
        assertEquals("10110010110110010110010010010110010", res[1]);
    }

    @Test
    public void otherTests() {
        String[] res = code.decode("12");
        assertEquals("NONE", res[0]);
        assertEquals("NONE", res[1]);
    }
}
