package com.springbank.user.core.dto;

import lombok.Data;

@Data
public class BaseResponse {
    private final String message;

    public BaseResponse(final String message) {
        this.message = message;
    }
}
