package com.example.calculator;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;

public class Main {
    private JTextField display;
    private String expression = "";

    public Main() {
        System.out.println("[DEBUG] Calculator initialized");
        createUI();
    }

    private void createUI() {
        JFrame frame = new JFrame("Calculator");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 400);
        frame.setLayout(new BorderLayout());

        display = new JTextField();
        display.setEditable(false);
        display.setFont(new Font("SansSerif", Font.PLAIN, 24));
        display.setHorizontalAlignment(SwingConstants.RIGHT);
        frame.add(display, BorderLayout.NORTH);

        JPanel panel = new JPanel(new GridLayout(4, 4, 5, 5));
        String[] buttons = {
            "7", "8", "9", "/",
            "4", "5", "6", "*",
            "1", "2", "3", "-",
            "C", "0", "=", "+"
        };

        for (String btn : buttons) {
            JButton button = new JButton(btn);
            button.setFont(new Font("SansSerif", Font.PLAIN, 18));
            button.addActionListener(e -> handleInput(btn));
            panel.add(button);
        }

        frame.add(panel, BorderLayout.CENTER);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }

    private void handleInput(String input) {
        System.out.println("[DEBUG] Button pressed: " + input);
        switch (input) {
            case "C" -> {
                expression = "";
                display.setText("");
            }
            case "=" -> calculate();
            default -> {
                expression += input;
                display.setText(expression);
            }
        }
    }

    private void calculate() {
        System.out.println("[DEBUG] Calculate triggered");
        System.out.println("[DEBUG] Expression: " + expression);
        
        try {
            List<Double> numbers = new ArrayList<>();
            List<Character> operators = new ArrayList<>();
            
            StringBuilder currentNum = new StringBuilder();
            for (char c : expression.toCharArray()) {
                if (c == '+' || c == '-' || c == '*' || c == '/') {
                    if (!currentNum.isEmpty()) {
                        numbers.add(Double.parseDouble(currentNum.toString()));
                        currentNum = new StringBuilder();
                    }
                    operators.add(c);
                } else {
                    currentNum.append(c);
                }
            }
            if (!currentNum.isEmpty()) {
                numbers.add(Double.parseDouble(currentNum.toString()));
            }

            System.out.println("[DEBUG] Numbers: " + numbers);
            System.out.println("[DEBUG] Operators: " + operators);

            double result = numbers.get(0);
            for (int i = 0; i < operators.size(); i++) {
                double next = numbers.get(i + 1);
                char op = operators.get(i);
                result = switch (op) {
                    case '+' -> result + next;
                    case '-' -> result - next;
                    case '*' -> result * next;
                    case '/' -> result / next;
                    default -> result;
                };
            }

            System.out.println("[DEBUG] Result: " + result);
            String output = (result == (long) result) 
                ? String.valueOf((long) result) 
                : String.valueOf(result);
            System.out.println("[DEBUG] Output: " + output);
            display.setText(output);
            expression = output;
        } catch (Exception e) {
            System.out.println("[DEBUG] Error: " + e.getMessage());
            display.setText("Error");
            expression = "";
        }
    }

    public static void main(String[] args) {
        System.out.println("[DEBUG] Main method started");
        SwingUtilities.invokeLater(() -> new Main());
    }
}
