/*
 This is a template file to generate the s-function for MAVLink message encoding.
 This file will not compile correctly, please use the Matlab script "create_sfun_encode.m"
 to create a compilable s-function.
 (c) Aditya Joshi, October 2017
 */
<BEGIN>
<EDIT><1> // #define S_FUNCTION_NAME  sfun_encode_msg_attitude
#define S_FUNCTION_LEVEL 2

#include "simstruc.h"

// System and Component IDs for MAVLink communication
<EDIT><2> // #define SYS_ID 100
<EDIT><3> // #define COMP_ID 200

<EDIT><4> // #include "include/mavlink/v1.0/common/mavlink.h"
<EDIT><5> // #include "include/sfun_mavlink_msg_attitude.h"

/* Function: mdlInitializeSizes ================================================
 * REQUIRED METHOD
 * Abstract:
 *    The sizes information is used by Simulink to determine the S-function
 *    block's characteristics (number of inputs, outputs, states, etc.).
 */
static void mdlInitializeSizes(SimStruct *S)
{

    DECL_AND_INIT_DIMSINFO(inputDimsInfo);
    DECL_AND_INIT_DIMSINFO(outputDimsInfo);

    ssSetNumSFcnParams(S, 0);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        return; /* Parameter mismatch will be reported by Simulink */
    }

    if (!ssSetNumInputPorts(S, 1)) return;

    ssSetInputPortWidth(S, 0, 1);
    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortRequiredContiguous(S, 0, 1);

    DTypeId BusType;
<EDIT><6> // ssRegisterTypeFromNamedObject(S, INPUT_BUS_NAME, &BusType);
    if(BusType == INVALID_DTYPE_ID) return;
    ssSetInputPortDataType(S, 0, BusType);
    ssSetBusInputAsStruct(S, 0, 1);
    ssSetInputPortBusMode(S, 0, SL_BUS_MODE);

    if (!ssSetNumOutputPorts(S, 1)) return;

    ssSetOutputPortWidth(S, 0, MAVLINK_MAX_PACKET_LEN);
    ssSetOutputPortDataType(S, 0, SS_UINT8);

    ssSetNumSampleTimes(S, 1);

    /* specify the sim state compliance to be same as a built-in block */
    ssSetSimStateCompliance(S, USE_DEFAULT_SIM_STATE);

    ssSetOptions(S, 0);   /* general options (SS_OPTION_xx) */

} /* end mdlInitializeSizes */


/* Function: mdlInitializeSampleTimes ==========================================
 * REQUIRED METHOD
 * Abstract:
 *    This function is used to specify the sample time(s) for your
 *    S-function. You must register the same number of sample times as
 *    specified in ssSetNumSampleTimes.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    /* Register one pair for each sample time */
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
    ssSetModelReferenceSampleTimeDefaultInheritance(S);

} /* end mdlInitializeSampleTimes */

/* Function: mdlStart ==========================================================
 * Abstract:
 *    This function is called once at start of model execution. If you
 *    have states that should be initialized once, this is the place
 *    to do it.
 */
#define MDL_START
static void mdlStart(SimStruct *S)
{
<EDIT><7> // int_T *busInfo = (int_T *) malloc(2*NFIELDS_INPUT_BUS*sizeof(int_T));
    if(busInfo == NULL) {
      ssSetErrorStatus(S, "Memory allocation failure");
      return;
    }
<EDIT><8> // encode_input_businfo(S, busInfo);

} /* end mdlStart */


/* Function: mdlOutputs ========================================================
 * REQUIRED METHOD
 * Abstract:
 *    In this function, you compute the outputs of your S-function
 *    block.
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
    const char *uvec = (const char *) ssGetInputPortSignal(S, 0);
    uint8_T *yvec = (uint8_T *) ssGetOutputPortSignal(S, 0);
    int_T* busInfo = (int_T *) ssGetUserData(S);
<EDIT><9> // encode_output_vector(uvec, busInfo, yvec);
}

/* Function: mdlTerminate ======================================================
 * REQUIRED METHOD
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
 static void mdlTerminate(SimStruct *S)
 {
     /* Free stored bus information */
     int_T *busInfo = (int_T *) ssGetUserData(S);
     if(busInfo != NULL) {
         free(busInfo);
     }
 }

/*=============================*
 * Required S-function trailer *
 *=============================*/

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif

<END>