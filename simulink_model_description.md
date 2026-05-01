# Simulink Model Description

## Overview
This document describes a simplified Simulink model for the RC car speed response.

The model represents the RC car as a first-order dynamic system. It can be used to study how the vehicle speed changes over time after a motor input command.

## Model Concept

```text
Speed Command
      ↓
Gain Block
      ↓
Transfer Function
      ↓
Vehicle Speed Output
      ↓
Scope
Transfer Function
G(s) = K / (tau*s + 1)

Where:

K is the system gain
tau is the time constant
s is the Laplace variable
Example Parameters
K = 2.5
tau = 1.2
Purpose

The purpose of this model is to understand the speed response, rise time, settling time and general vehicle behavior of a simplified RC car system.

Future Improvements
Add PID speed control
Add PWM input simulation
Add real motor parameters
Compare simulation results with measured test data
Add screenshots of the Simulink model
