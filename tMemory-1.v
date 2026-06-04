`timescale 1ns/1ps

module tb_memory;

    //------------------------------------------------------------
    // RAM SIGNALS
    //------------------------------------------------------------

    reg Reset;
    reg Clock;
    reg OE;
    reg WE;

    reg  [29:0] Address;
    reg  [31:0] DataIn;
    wire [31:0] DataOut;

    //------------------------------------------------------------
    // REGISTER BANK SIGNALS
    //------------------------------------------------------------

    reg  [4:0] ReadReg1;
    reg  [4:0] ReadReg2;
    reg  [4:0] WriteReg;

    reg  [31:0] WriteData;
    reg         WriteCmd;

    wire [31:0] ReadData1;
    wire [31:0] ReadData2;

    //------------------------------------------------------------
    // DUT INSTANTIATION
    //------------------------------------------------------------

    RAM ram0 (
        .Reset(Reset),
        .Clock(Clock),
        .OE(OE),
        .WE(WE),
        .Address(Address),
        .DataIn(DataIn),
        .DataOut(DataOut)
    );

    Registers reg0 (
        .ReadReg1(ReadReg1),
        .ReadReg2(ReadReg2),
        .WriteReg(WriteReg),
        .WriteData(WriteData),
        .WriteCmd(WriteCmd),
        .ReadData1(ReadData1),
        .ReadData2(ReadData2)
    );

    //------------------------------------------------------------
    // CLOCK TASK
    //------------------------------------------------------------

    task do_clock;
    begin
        #5 Clock = 1;
        #5 Clock = 0;
    end
    endtask

    //------------------------------------------------------------
    // MAIN TESTBENCH
    //------------------------------------------------------------

    initial begin

        //--------------------------------------------------------
        // INITIALIZATION
        //--------------------------------------------------------

        Clock     = 0;
        Reset     = 0;
        OE        = 1;
        WE        = 0;

        Address   = 0;
        DataIn    = 0;

        ReadReg1  = 0;
        ReadReg2  = 0;
        WriteReg  = 0;
        WriteData = 0;
        WriteCmd  = 0;

        #20;

        //========================================================
        // EXAMPLE TEST CASE
        //========================================================

        //--------------------------------------------------------
        // TEST 1 : RAM WRITE / READ
        //--------------------------------------------------------
        // Objective:
        //     Verify correct RAM write and read operations.
        //
        // Procedure:
        //     1. Enable RAM write
        //     2. Write data into memory address 0
        //     3. Disable write
        //     4. Enable output
        //     5. Read data back
        //
        // Expected Result:
        //     DataOut should equal:
        //         32'h11111111
        //--------------------------------------------------------

        $display("TEST 1 : RAM WRITE / READ");

        // WRITE OPERATION
        WE      = 1;
        OE      = 1;

        Address = 0;
        DataIn  = 32'h11111111;

        do_clock();

        // READ OPERATION
        WE      = 0;
        OE      = 0;

        #10;

        $display("Address 0 = %h", DataOut);



        //--------------------------------------------------------
        // TODO #2 : RAM RESET
        //--------------------------------------------------------
        // Objective:
        //     Verify reset clears all RAM locations.
        //
        // Procedure:
        //     1. Assert Reset = 1
        //     2. Wait for several nanoseconds
        //     3. Deassert Reset
        //     4. Read multiple RAM addresses
        //
        // Expected Result:
        //     All memory locations output:
        //         32'h00000000
        //--------------------------------------------------------
		  
		   $display("TEST 2 : RAM RESET");

        // 1. Assert Reset
        Reset = 1;
        
        // 2. Wait for several nanoseconds
        #20;
        
        // 3. Deassert Reset
        Reset = 0;
        WE    = 0;
        OE    = 0; 

        // 4. Read multiple RAM addresses
        Address = 0;
        #10;
        $display("Address 0 after reset = %h", DataOut);

        Address = 4;
        #10;
        $display("Address 4 after reset = %h", DataOut);


        //--------------------------------------------------------
        // TODO #7 : FALLING EDGE VERIFICATION
        //--------------------------------------------------------
        // Objective:
        //     Verify RAM writes only on falling clock edge.
        //
        // Procedure:
        //     1. Change DataIn before rising edge
        //     2. Toggle clock
        //     3. Observe when RAM updates
        //
        // Expected Result:
        //     RAM updates only after falling edge
        //--------------------------------------------------------
		  $display("TEST 7 : FALLING EDGE VERIFICATION");

        WE      = 1;
        OE      = 0;
        Address = 8;
        
        // 1. Change DataIn before rising edge
        DataIn  = 32'hABABABAB;

        // 2. Toggle clock step-by-step (instead of using do_clock task)
        #5 Clock = 1; 
        #2;           
        $display("Mid-pulse (Clock=1) RAM Output = %h", DataOut);

        #3 Clock = 0; 
        #2;           
        $display("Post-falling edge (Clock=0) RAM Output = %h", DataOut);

        WE      = 0;



        //--------------------------------------------------------
        // TODO #8 : SINGLE REGISTER WRITE
        //--------------------------------------------------------
        // Objective:
        //     Verify writing to register a0.
        //
        // Procedure:
        //     1. Set WriteReg = 5'b01010
        //     2. Enable WriteCmd
        //     3. Write known data
        //     4. Read register back
        //
        // Expected Result:
        //     ReadData outputs written value
        //--------------------------------------------------------
		  $display("TEST 8 : SINGLE REGISTER WRITE");

        // 1. Set WriteReg = 5'b01010 (Register 10, typically 'a0' in RISC-V)
        WriteReg  = 5'b01010;
        
        // 2. Enable WriteCmd
        WriteCmd  = 1;
        
        // 3. Write known data
        WriteData = 32'hC0DEF00D;

        do_clock(); 
        
        // 4. Read register back (routing to ReadReg1)
        WriteCmd  = 0;
        ReadReg1  = 5'b01010;
        #10;

        $display("Register a0 Read Data = %h", ReadData1);


        //--------------------------------------------------------
        // END SIMULATION
        //--------------------------------------------------------

        #100;

        $display("ALL TESTS COMPLETE");

        $finish;

    end

endmodule
