package com.credits.credits.credits.controller;

import com.credits.credits.credits.model.CreditCount;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.CookieValue;
import org.springframework.web.bind.annotation.RequestMapping;

import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletResponse;
import java.io.*;
import javax.xml.bind.DatatypeConverter;
import java.util.Objects;
import java.util.zip.GZIPOutputStream;
import java.util.zip.GZIPInputStream;

import static org.springframework.web.bind.annotation.RequestMethod.GET;

@Controller
public class CreditsController {

    @RequestMapping(value = "/**", method = {GET})
    public String index(@CookieValue(value = "counter", defaultValue = "") String counter, Model model, HttpServletResponse resp) throws IOException, ClassNotFoundException {
        CreditCount count;
        if (Objects.equals(counter, "")) {
            count = new CreditCount(0);
        } else {
            try (ObjectInputStream s = new ObjectInputStream(new GZIPInputStream(new ByteArrayInputStream(DatatypeConverter.parseBase64Binary(counter))))) {
                count = (CreditCount) s.readObject();
            }
        }
        count.increment();

        ByteArrayOutputStream os = new ByteArrayOutputStream();
        try (ObjectOutputStream s = new ObjectOutputStream(new GZIPOutputStream(os))) {
            s.writeObject(count);
        }

        Cookie cookie = new Cookie("counter", new String(DatatypeConverter.printBase64Binary(os.toByteArray())));
        cookie.setHttpOnly(true);
        resp.addCookie(cookie);

        model.addAttribute("count", count.getValue());
        model.addAttribute("won", count.getValue() > 2000000000L);

        return "index";
    }

}
