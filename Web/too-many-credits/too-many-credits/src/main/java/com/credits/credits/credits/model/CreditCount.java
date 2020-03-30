package com.credits.credits.credits.model;

import java.io.Serializable;

public class CreditCount implements Serializable {
    private long value;

    public CreditCount() {
        value = 0;
    }

    public CreditCount(long value) {
        this.value = value;
    }

    public void increment() {
        value++;
    }

    public long getValue() {
        return value;
    }

    public void setValue(long value) {
        this.value = value;
    }
}
